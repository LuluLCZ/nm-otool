/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho32_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:50:56 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:51:04 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int								check_bad_string_32(char *str, t_file file)
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

t_info							*fill_data(t_info *data,\
struct nlist *symtab)
{
	data->n_type = ((struct nlist *)symtab)->n_type;
	data->n_sect = ((struct nlist *)symtab)->n_sect;
	data->value = ft_memalloc(256);
	return (data);
}

void							parse_mach_32_symtab(\
struct symtab_command *sym, t_file file, t_mysects *sections, t_info *data)
{
	uint32_t					i;
	void						*symtab;

	i = 0;
	symtab = (void *)file.ptr + ifswap32(sym->symoff, file.reverse);
	while (i < ifswap32(sym->nsyms, file.reverse))
	{
		data->symname = check_string(symtab, file, sym);
		if (ft_strlen(data->symname) == 0 || (data->symname == NULL))
			data->name_not_found = true;
		data = fill_data(data, (struct nlist *)symtab);
		ft_putnbr_base(ifswap32((\
		(struct nlist *)symtab)->n_value, file.reverse), 16, data->value);
		data->symbol_letter = get_symbol_letter(data, sections,\
		ifswap32(((struct nlist *)symtab)->n_value, file.reverse));
		if (data->value)
			data->value = adding_0(data->value,\
			data->symbol_letter, 32, data->symname);
		data = refresh_symbol(data);
		symtab += sizeof(struct nlist);
		i++;
	}
	print_data(sort_names(data));
}

void							hexdump(char *ptr, int size)
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

void							first_hexdump(\
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
		tmp = adding_0(tmp, 'T', 32, "none");
		ft_putstr(tmp);
		ft_putchar('\t');
		hexdump(start, len);
		start += 16;
		sect_addr += 16;
		size = size - 16;
		len = size > 16 ? 16 : size;
		free(tmp);
	}
}
