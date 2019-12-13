/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:43:59 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/13 22:42:08 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"


int	check_bad_string_32(char *str, t_file file)
{
	int		i;

	if ((void *)str >= file.ptr + file.size || (void *)str < file.ptr)
		return (-1);
	i = 0;
	while ((void *)str + i < file.ptr + file.size - 1 && str[i])
		i++;
	if (str[i])
		return(i);
	return (0);
}

void parse_mach_32_symtab(struct symtab_command *sym, t_file file, t_mysects *sections, t_info *data)
{
	uint32_t			i;
	void		*symtab;

	i = 0;
	symtab = (void *)file.ptr + ifswap32(sym->symoff, file.reverse);
	while (i < ifswap32(sym->nsyms, file.reverse))
	{
		data->symname = check_string(symtab, file, sym);
		if (ft_strlen(data->symname) == 0 || (data->symname == NULL))
			data->name_not_found = true;
		data->n_type = ((struct nlist *)symtab)->n_type;
		data->n_sect = ((struct nlist *)symtab)->n_sect;
		data->value = (char *)malloc(sizeof(char *) * 256);
		ft_putnbr_base(ifswap32((\
		(struct nlist *)symtab)->n_value, file.reverse), 16, data->value);
		data->symbol_letter = get_symbol_letter(data, sections,\
		ifswap32(((struct nlist *)symtab)->n_value, file.reverse));
		data->value = adding_0(data->value,\
		data->symbol_letter, 32, data->symname);
		data = refresh_symbol(data);
		symtab += sizeof(struct nlist);
		i++;
	}
	print_data(sort_names(data));
}

t_mysects	*parse_mach_32_segment(void *sc, t_mysects *sections, t_file file)
{
	void						*section;
	uint32_t					nsects;
	uint32_t					i;

	section = sc + sizeof(struct segment_command);
	nsects = ifswap32(((struct segment_command *)sc)->nsects, file.reverse);
	i = 0;
	while (i < nsects)
	{
		if (error_1(i, ifswap32(((struct section *)section)->size,\
			file.reverse), 0, file) == -1)
			return (NULL);
		sections->address = ifswap32(((struct section *)section)->addr,\
		file.reverse);
		sections->index = sections->prev ? sections->prev->index + 1 : 1;
		sections->name = ft_strdup(((struct section *)section)->sectname);
		sections->size = ifswap32(((struct section *)section)->size,\
		file.reverse);
		sections = refresh_mysect(sections);
		section = section + sizeof(struct section);
		i++;
	}
	return (sections);
}

int								check_load_command(t_file file,\
			void *header, struct load_command *lc, uint32_t ncmds)
{
	uint32_t					i;
	struct segment_command	*sc;

	i = 0;
	if (error_2(ncmds, file, 0, 0, 0) == -1)
		return (-1);
	while (i < ncmds)
	{
		if (error_3(lc, file, i, header) == -1)
			return (-1);
		if (error_2(ncmds, file, 1, i,\
			ifswap32(lc->cmdsize, file.reverse)) == -1)
			return (-1);
		if (ifswap32(lc->cmd, file.reverse) == LC_SEGMENT)
		{
			sc = (struct segment_command *)lc;
			if (error_SEG_1(sc, lc, i, file) == -1)
				return (-1);
		}
		lc = (void *)lc + ifswap32(lc->cmdsize, file.reverse);
		i++;
	}
	return (0);
}

int							handle_32(void *header, t_file file)
{
	uint32_t					ncmds;
	uint32_t					i;
	struct load_command			*lc;
	t_mysects					*sections;
	t_info						*data;

	sections = init_mysect();
	ncmds = ifswap32(((struct mach_header *)header)->ncmds, file.reverse);
	i = 0;
	lc = (void *)file.ptr + sizeof(struct mach_header);
	data = init_mysymbol();
	if (check_load_command(file, header, lc, ncmds) == -1)
		return (-1);
	while (i < ncmds)
	{
		if (handle_symtab(lc, data, file, sections) == -1)
			return (-1);
		lc = (void *)lc + ifswap32(lc->cmdsize, file.reverse);
		i++;
	}
	return (0);
}