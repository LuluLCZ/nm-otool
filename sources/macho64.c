/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:07:02 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/07 16:19:51 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

char			hex_digit(int v)
{
	if (v >= 0 && v < 10)
		return ('0' + v);
	else
		return ('a' + v - 10);
}

void			print_address_hex(void *p0)
{
	int				i;
	uintptr_t		p;

	p = (uintptr_t)p0;
	ft_putstr("0x");
	i = (sizeof(p) << 2) - 4;
	while (i >= 0)
	{
		i -= 4;
		ft_putchar(hex_digit((p >> i) & 0xf));
	}
}

void			free_sections(t_mysects *sections)
{
	t_mysects *tmp;

	sections = go_begin(sections);
	while (sections)
	{
		if (sections->next)
			tmp = sections->next;
		free(sections->name);
		if (sections->next)
		{
			free(sections);
			sections = tmp;
			tmp = NULL;
		}
		else
			break ;
	}
	free(sections);
}

void	ft_putnbr_base_otool(size_t n, size_t base, char *str)
{
	if (base == 10)
		ft_putnbr(n);
	else if (n < 0)
		ft_putchar('0');
	else
	{
		if (n <= 15)
			str[ft_strlen(str)] = '0';
		if (n >= base)
			ft_putnbr_base(n / base, base, str);
		if (n % base < 10)
			str[ft_strlen(str)] = ((n % base) + 48);
		else
			str[ft_strlen(str)] = ((n % base) - 10 + 65);
	}
}


int								check_bad_string(char *str, t_file file)
{
	int							i;

	if ((void *)str >= file.ptr + file.size || (void *)str < file.ptr)
		return (-1);
	i = 0;
	while ((void *)str + i < file.ptr + file.size - 1 && str[i])
		i++;
	if (str[i])
		return (i);
	return (0);
}

void							parse_mach_64_symtab(\
struct symtab_command *sym, t_file file, t_mysects *sections, t_info *data)
{
	uint32_t					i;
	void						*symtab;

	i = 0;
	symtab = (void *)file.ptr + ifswap32(sym->symoff, file.reverse);
	while (i < ifswap32(sym->nsyms, file.reverse))
	{
		data->symname = check_string_64(symtab, file, sym);
		if (ft_strlen(data->symname) == 0 || (data->symname == NULL))
			data->name_not_found = true;
		data->n_type = ((struct nlist_64 *)symtab)->n_type;
		data->n_sect = ((struct nlist_64 *)symtab)->n_sect;
		data->value = ft_memalloc(256);
		ft_putnbr_base(ifswap64((\
		(struct nlist_64 *)symtab)->n_value, file.reverse), 16, data->value);
		data->symbol_letter = get_symbol_letter(data, sections,\
		ifswap64(((struct nlist_64 *)symtab)->n_value, file.reverse));
		if (data->value) data->value = adding_0(data->value, data->symbol_letter, 64, data->symname);
		data = refresh_symbol(data);
		symtab += sizeof(struct nlist_64);
		i++;
	}
	print_64_data(sort_names(data));
}

void							hexdump_64(char *ptr, int size)
{
	int							i;
	char						*tmp;

	tmp = ft_memalloc(52);
	i = 0;
	while (i < size)
	{
		// print_address_hex(ptr);
		ft_putnbr_base_otool((uint8_t)ptr[i], 16, tmp);
		tmp[ft_strlen(tmp)] = ' ';
		i++;
	}
	tmp = ft_str_lowerchar(tmp);
	ft_putendl(tmp);
	free(tmp);
}

void							first_hexdump_64(int64_t size, void *start, int64_t sect_addr, t_file file)
{
	int64_t len;
	char	*tmp;

	len = size > 16 ? 16 : size;
	(void)file;
	while (len > 0)
	{
		tmp = ft_memalloc(256 * 50);
		ft_putnbr_base(sect_addr, 16, tmp);
		tmp = adding_0(tmp, 'T', 64, "none");
		ft_putstr(tmp);
		ft_putchar('\t');
		hexdump_64(start, len);
		start += 16;
		sect_addr += 16;
		size = size - 16;
		len = size > 16 ? 16 : size;
		free(tmp); 
	}
}

t_mysects						*parse_mach_64_segment(void *sc,\
	t_mysects *sections, t_file file)
{
	void						*section;
	uint32_t					nsects;
	uint32_t					i;

	section = sc + sizeof(struct segment_command_64);
	nsects = ifswap64(((struct segment_command_64 *)sc)->nsects, file.reverse);
	i = 0;
	while (i < nsects)
	{
		if (error_64_1(i, ifswap64(((struct section_64 *)section)->size,\
			file.reverse), 0, file) == -1)
			{
				free_sections(sections);
				return (NULL);
			}
		sections->address = ifswap64(((struct section_64 *)section)->addr, file.reverse);
		sections->offset = ifswap64(((struct section_64 *)section)->offset, file.reverse);
		sections->index = sections->prev ? sections->prev->index + 1 : 1;
		sections->name = ft_strdup(((struct section_64 *)section)->sectname);
		sections->size = ifswap64(((struct section_64 *)section)->size,\
		file.reverse);
		if (!ft_strcmp(sections->name, SECT_TEXT) && !ft_strcmp(file.bin, BIN_OTOOL))
		{
			ft_putstr(file.filename);
			ft_putstr(":\nContents of (__TEXT,__text) section\n");
			first_hexdump_64(sections->size, (void *)file.ptr + sections->offset, sections->address, file);
			free_sections(sections);
			return (NULL);
		}
		sections = refresh_mysect(sections);
		section = section + sizeof(struct section_64);
		i++;
	}
	return (sections);
}

int								check_load_command_64(t_file file,\
			void *header, struct load_command *lc, uint32_t ncmds)
{
	uint32_t					i;
	struct segment_command_64	*sc;

	i = 0;
	if (error_64_2(ncmds, file, 0, 0, 0) == -1)
		return (-1);
	while (i < ncmds)
	{
		if (error_64_3(lc, file, i, header) == -1)
			return (-1);
		if (error_64_2(ncmds, file, 1, i,\
			ifswap32(lc->cmdsize, file.reverse)) == -1)
			return (-1);
		if (ifswap32(lc->cmd, file.reverse) == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64 *)lc;
			if (error_64_SEG_1(sc, lc, i, file) == -1)
				return (-1);
		}
		lc = (void *)lc + ifswap32(lc->cmdsize, file.reverse);
		i++;
	}
	return (0);
}

void			free_info(t_info *data)
{
	t_info *tmp;

	data = go_begin_info(data);
	while (data)
	{
		if (data->next)
			tmp = data->next;
		free(data->symname);
		free(data->value);
		if (data->next)
		{
			free(data);
			data = tmp;
			tmp = NULL;
		}
		else
			break ;
	}
	free(data);
}

int								handle_64(void *header, t_file file)
{
	uint32_t					ncmds;
	uint32_t					i;
	struct load_command			*lc;
	t_mysects					*sections;
	t_info						*data;
	struct segment_command_64	*sc;
	struct symtab_command		*sym;

	ncmds = ifswap64(((struct mach_header_64 *)header)->ncmds, file.reverse);
	i = 0;
	lc = (void *)file.ptr + sizeof(struct mach_header_64);
	if (check_load_command_64(file, header, lc, ncmds) == -1)
		return (-1);
	sections = init_mysect();
	data = init_mysymbol();
	while (i < ncmds)
	{
		if (ifswap32(lc->cmd, file.reverse) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (error_SYM(sym, file) == -1 || error_SYMOFF(sym, file, i) == -1)
				break;
			parse_mach_64_symtab(sym, file, sections, data);
		}
		else if (ifswap32(lc->cmd, file.reverse) == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64 *)lc;
			if ((sections = parse_mach_64_segment(sc, sections, file)) == NULL)
				break;
		}
		lc = (void *) lc + ifswap32(lc->cmdsize, file.reverse);
		i++;
	}
	free_sections(sections);
	free_info(data);
	return (0);
}
