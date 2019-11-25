/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:51:32 by llacaze           #+#    #+#             */
/*   Updated: 2019/11/21 16:53:27 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"
#include "libft.h"

void	ft_putnbr_base(size_t n, size_t base, char *str)
{
	if (base == 10)
		ft_putnbr(n);
	else if (n < 0)
		ft_putchar('0');
	else
	{
		if (n >= base)
			ft_putnbr_base(n / base, base, str);
		if (n % base < 10)
			str[ft_strlen(str)] = ((n % base) + 48);
		else
			str[ft_strlen(str)] = ((n % base) - 10 + 65);
	}
}

t_mysects	*find_section_from_nsect(t_mysects *sections, uint32_t nsect)
{
	sections = go_begin(sections);
	while (sections)
	{
		if (sections->index == nsect) return sections;
		sections = sections->next;
	}
	return (NULL);
}

char	check_for_section(t_info *data, t_mysects *sections)
{
	t_mysects	*right_sect;

	if ((right_sect = find_section_from_nsect(sections, data->n_sect)))
	{
		printf("|%d|", (bool)(ft_strcmp(right_sect->name, SECT_DATA)));
		if (!ft_strcmp(right_sect->name, SECT_TEXT))
			return ('T');
		else if (!ft_strcmp(right_sect->name, SECT_DATA))
			return ('D');
		else if (!ft_strcmp(right_sect->name, SECT_BSS))
			return ('B');
		else
			return ('S');
		if (!(data->n_type & N_EXT))
			return (data->n_type - 'A' - 'a');
	}
	return 'k';
}

char	get_symbol_letter(t_info *data, t_mysects *sections)
{
	if (N_STAB & data->n_type)
		return '-';
	else if ((N_TYPE & data->n_type) == N_UNDF)
	{
		if (data->name_not_found)
			return 'C';
		else if (data->n_type & N_EXT)
			return 'U';
		else
			return '?';
	}
	else if ((N_TYPE & data->n_type) == N_SECT)
		// return 'T';
		return check_for_section(data, sections); //For the moment we don't have sections so we'll just put S
		// return (match_symbol_section(saved_sections, data));
	else if ((N_TYPE & data->n_type) == N_ABS)
		return 'A';
	else if ((N_TYPE & data->n_type) == N_INDR)
		return 'I';
	return 'p';
}

char		*ft_str_lowerchar(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

char		*adding_0(char *str)
{
	int		i;
	char	*dump;

	dump = ft_strnew(32);
	i = 0;
	while (i < 16 - ft_strlen(str))
	{
		dump[i] = '0';
		i++;
	}
	dump[i] = '\0';
	if (ft_strlen(str) == 1) return ("                ");
	return (ft_str_lowerchar(ft_strjoin(dump, str)));
}

void parse_mach_64_symtab(struct symtab_command *sym, char *ptr, t_mysects *sections, t_info *data)
{
	uint32_t			i;
	void		*strtab;
	void		*symtab;
	char		*zero = (char *)malloc(sizeof(char *) + 52);

	i = 0;
	strtab = (void *)ptr + sym->stroff;
	symtab = (void *)ptr + sym->symoff;
	while (i < sym->nsyms)
	{
		data->symname = ft_strdup(strtab + ((struct nlist_64 *)symtab)->n_un.n_strx);
		if (ft_strlen(data->symname) == 0) data->name_not_found = true;
		else data->name_not_found = false;
		data->n_type = ((struct nlist_64 *)symtab)->n_type;
		data->n_sect = ((struct nlist_64 *)symtab)->n_sect;
		data->symbol_letter = get_symbol_letter(data, sections);
		data->value = (char *)malloc(sizeof(char *) * 256);
		ft_putnbr_base(((struct nlist_64 *)symtab)->n_value, 16, data->value);
		data->value = adding_0(data->value);
		if (data->name_not_found == false && !(N_STAB & data->n_type)) printf("%s %c %s\n", data->value, data->symbol_letter, data->symname);
		data = refresh_symbol(data);
		symtab += sizeof(struct nlist_64);
		i++;
	}
}

t_mysects	*parse_mach_64_segment(void *sc, t_mysects *sections)
{
	void		*section;
	uint32_t				nsects;
	uint32_t						i;

	section = sc + sizeof(struct segment_command_64);
	nsects = ((struct segment_command_64 *)sc)->nsects;
	i = 0;
	while (i < nsects)
	{
		sections->address = ((struct section_64 *)section)->addr;
		sections->index = sections->prev ? sections->prev->index + 1 : i;
		sections->name = ft_strdup(((struct section_64 *)section)->sectname);
		sections->size = ((struct section_64 *)section)->size;
		printf("name of section: %s, index of section: %llu, address of section: %llu, size of section: %llu\n", sections->name, sections->index, sections->address, sections->size);
		sections = refresh_mysect(sections);
		section = section + sizeof(struct section_64);
		i++;
	}
	return (sections);
}

void	parse_load_command(struct load_command *lc)
{
	uint32_t	cmd;

	cmd = lc->cmd;
	if (cmd == LC_SEGMENT) puts("SEGMENT");
	if (cmd == LC_SYMTAB) puts("SYMTAB");
}

void handle_64(char *ptr)
{
	uint32_t ncmds;
	uint32_t i;
	struct mach_header_64 *header;
	struct load_command *lc;
	struct segment_command_64 *sc;
	struct symtab_command *sym;
	t_mysects				*sections;
	t_info					*data;

	header = (struct mach_header_64 *)ptr;
	sections = init_mysect();
	ncmds = header->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	data = init_mysymbol();
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			// sections = sections + sizeof(struct s_section);
			// printf("number of sections: %d\nname of first section: %s\nflags: %d\n", sc->nsects, sections->sectname, sc->flags);
			// if (!ft_strcmp(sections->sectname))
			// printf("number of sections: %d\nname of first section: %s\n", sc->nsects, sections->sectname);
			parse_mach_64_symtab(sym, ptr, sections, data);
			break;
		}
		else if (lc->cmd == LC_SEGMENT_64)
		{
			puts("SEGMENT 64");
			sc = (struct segment_command_64 *)lc;
			sections = parse_mach_64_segment(sc, sections);
		}
		else if (lc->cmd == LC_SEGMENT)
			puts("SEGMENT");
		lc = (void *) lc + lc->cmdsize;
		i++;
	}
}

void nm(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *) ptr;
	if (magic_number == MH_MAGIC)
	{
		// puts("Binaire pour 32-bits");
	}
	if (magic_number == MH_MAGIC_64)
	{
		// puts("Binaire pour 64-bits");
		handle_64(ptr);
	}
}

int main(int ac, char **av)
{
	int fd;
	char *ptr;
	struct stat buf;

	if (ac != 2)
	{
		fprintf(stderr, "give args");
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if ((fstat(fd, &buf)) < 0)
	{
		perror("fstat");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}