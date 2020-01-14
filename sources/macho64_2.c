/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:53:21 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:53:28 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

t_info							*fill_data_64(t_info *data,\
struct nlist_64 *symtab)
{
	data->n_type = ((struct nlist_64 *)symtab)->n_type;
	data->n_sect = ((struct nlist_64 *)symtab)->n_sect;
	data->value = ft_memalloc(256);
	return (data);
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
		data = fill_data_64(data, (struct nlist_64 *)symtab);
		ft_putnbr_base(ifswap64((\
		(struct nlist_64 *)symtab)->n_value, file.reverse), 16, data->value);
		data->symbol_letter = get_symbol_letter(data, sections,\
		ifswap64(((struct nlist_64 *)symtab)->n_value, file.reverse));
		if (data->value)
			data->value = adding_0(data->value,\
			data->symbol_letter, 64, data->symname);
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
		ft_putnbr_base_otool((uint8_t)ptr[i], 16, tmp);
		tmp[ft_strlen(tmp)] = ' ';
		i++;
	}
	tmp = ft_str_lowerchar(tmp);
	ft_putendl(tmp);
	free(tmp);
}

void							first_hexdump_64(\
int64_t size, void *start, int64_t sect_addr, t_file file)
{
	int64_t						len;
	char						*tmp;

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

t_mysects						*f_sect_64(\
struct section_64 *section, t_file file, t_mysects *sections)
{
	sections->address = ifswap64(\
	((struct section_64 *)section)->addr, file.reverse);
	sections->offset = ifswap64(\
	((struct section_64 *)section)->offset, file.reverse);
	sections->index = sections->prev ? sections->prev->index + 1 : 1;
	sections->name = ft_strdup(((struct section_64 *)section)->sectname);
	sections->size = ifswap64(((struct section_64 *)section)->size,\
	file.reverse);
	return (sections);
}
