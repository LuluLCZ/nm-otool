/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:51:32 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/03 16:32:10 by llacaze          ###   ########.fr       */
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

char		global_case_symbol(uint8_t n_type, char c)
{
	if (!(n_type & N_EXT))
		return (ft_tolower(c));
	else
		return (c);
}

t_mysects	*find_section_from_nsect(t_mysects *sections, uint32_t nsect)
{
	sections = go_begin(sections);
	while (sections)
	{
		// printf("%llu -> index, %u -> nsect", sections->index, nsect);
		if (sections->index == nsect) return sections;
		sections = sections->next;
	}
	return (NULL);
}

char	check_for_section(t_info *data, t_mysects *sections)
{
	t_mysects	*right_sect;

	// printf("%llu -> data->n_sect", data->n_sect);
	if ((right_sect = find_section_from_nsect(sections, data->n_sect)))
	{
		if (!right_sect->name)
		{
			return (global_case_symbol(data->n_type, 'S'));
		}
		// printf("|%d|", (bool)(ft_strcmp(right_sect->name, SECT_DATA)));
		if (!ft_strcmp(right_sect->name, SECT_TEXT))
			return (global_case_symbol(data->n_type, 'T'));
		else if (!ft_strcmp(right_sect->name, SECT_DATA))
			return (global_case_symbol(data->n_type, 'D'));
		else if (!ft_strcmp(right_sect->name, SECT_BSS))
			return (global_case_symbol(data->n_type, 'B'));
		else if (!ft_strcmp(right_sect->name, SECT_COMMON))
			return (global_case_symbol(data->n_type, 'S'));
		else
			return (global_case_symbol(data->n_type, 'S'));
		// if (!(data->n_type & N_EXT))
			// return (data->n_type - 'A' - 'a');
	}
	return '-';
}

char	get_symbol_letter(t_info *data, t_mysects *sections)
{
	if ((N_TYPE & data->n_type) == N_SECT)
		return check_for_section(data, sections);
	else if (N_STAB & data->n_type)
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
	 //For the moment we don't have sections so we'll just put S
		// return (match_symbol_section(saved_sections, data));
	else if ((N_TYPE & data->n_type) == N_ABS)
		return (global_case_symbol(data->n_type, 'A'));
	else if ((N_TYPE & data->n_type) == N_INDR)
		return (global_case_symbol(data->n_type, 'I'));
	return ' ';
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

t_info		*sort_names(t_info *data)
{
	t_info *head;

	data = go_begin_info(data);
	head = data;
	if (data->next->symname != NULL && data->symname != NULL && data->next->next != NULL)
	{
		while (data->next->next)
		{
			if (ft_strcmp(data->symname, data->next->symname) > 0)
			{
				data = ft_swap_double(data, data->next, &head);
				data = go_begin_info(data);
			}
			else
				data = data->next;
		}
	}
	return data;
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
		// if (data->name_not_found == false && !(N_STAB & data->n_type)) printf("%s %c %s\n", data->value, data->symbol_letter, data->symname);
		data = refresh_symbol(data);
		symtab += sizeof(struct nlist_64);
		i++;
	}
	data = sort_names(data);
	data = go_begin_info(data);
	while (data->next)
	{
		if (data->name_not_found == false && !(N_STAB & data->n_type)) printf("%s %c %s\n", data->value, data->symbol_letter, data->symname);
		data = data->next;
	}
}

t_mysects	*parse_mach_64_segment(void *sc, t_mysects *sections)
{
	void					*section;
	uint32_t				nsects;
	uint32_t				i;

	section = sc + sizeof(struct segment_command_64);
	nsects = ((struct segment_command_64 *)sc)->nsects;
	i = 0;
	while (i < nsects)
	{
		sections->address = ((struct section_64 *)section)->addr;
		sections->index = sections->prev ? sections->prev->index + 1 : 1;
		sections->name = ft_strdup(((struct section_64 *)section)->sectname);
		sections->size = ((struct section_64 *)section)->size;
		// printf("name of section: %s, index of section: %llu, address of section: %llu, size of section: %llu\n", sections->name, sections->index, sections->address, sections->size);
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

void handle_64(char *ptr, void *header)
{
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;
	struct segment_command_64 *sc;
	struct symtab_command *sym;
	t_mysects				*sections;
	t_info					*data;

	sections = init_mysect();
	ncmds = ((struct mach_header_64 *)header)->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	data = init_mysymbol();
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			parse_mach_64_symtab(sym, ptr, sections, data);
			// break;
		}
		else if (lc->cmd == LC_SEGMENT_64)
		{
			// puts("SEGMENT 64");
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
	unsigned int	magic_number;
	void			*header;

	magic_number = *(int *) ptr;
	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		puts("Binaire pour 32-bits");
		header = (struct mach_header *)ptr;
	}
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		// puts("Binaire pour 64-bits");
		header = (struct mach_header *)ptr;
		handle_64(ptr, header);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		puts("Binaire fat 32-bits");
		header = (struct fat_header *)ptr;
	}
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
	{
		puts("Binaire fat 64-bits");
		header = (struct fat_header_64 *)ptr;
	}
	else
	{
		puts("The file was not recognized as a valid object file");
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