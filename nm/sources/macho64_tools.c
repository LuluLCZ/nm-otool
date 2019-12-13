/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 21:45:23 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/13 22:24:28 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int								handle_64_symtab(struct load_command *lc,\
	t_info *data, t_file file, t_mysects *sections)
{
	struct symtab_command		*sym;
	struct segment_command_64	*sc;

	if (ifswap32(lc->cmd, file.reverse) == LC_SYMTAB)
	{
		sym = (struct symtab_command *)lc;
		if (error_64_SYM(sym, file) == -1)
			return (-1);
		parse_mach_64_symtab(sym, file, sections, data);
	}
	else if (ifswap32(lc->cmd, file.reverse) == LC_SEGMENT_64)
	{
		sc = (struct segment_command_64 *)lc;
		if ((sections = parse_mach_64_segment(sc, sections, file)) == NULL)
			return (-1);
	}
	return (0);
}

void							print_64_data(t_info *data)
{
	data = go_begin_info(data);
	while (data->next)
	{
		if ((data->name_not_found == true && (data->symbol_letter == '?' ||\
		data->symbol_letter == 'U')) ||\
		(data->name_not_found == false && !(N_STAB & data->n_type)))
		{
			ft_putstr(data->value);
			ft_putchar(' ');
			ft_putchar(data->symbol_letter);
			ft_putchar(' ');
			if (data->symbol_letter == 'I')
			{
				ft_putstr(data->symname);
				ft_putstr(" (indirect for ");
				ft_strcmp(data->symname, "bad string index") == 0 ?\
					ft_putstr("?") : ft_putstr(data->symname);
				ft_putendl(")");
			}
			else
				ft_putendl(data->symname);
		}
		data = data->next;
	}
}

char							*check_string_64(void *symtab,\
					t_file file, struct symtab_command *sym)
{
	int							i;
	void						*strtab;

	strtab = (void *)file.ptr + ifswap32(sym->stroff, file.reverse);
	i = check_bad_string(strtab + ifswap32(\
		((struct nlist_64 *)symtab)->n_un.n_strx, file.reverse), file);
	if (i == -1)
		return (ft_strdup("bad string index"));
	else if (i != 0)
		return (ft_strdup_size(strtab +\
		ifswap32(((struct nlist_64 *)symtab)->n_un.n_strx,\
		file.reverse), i));
	else
		return (ft_strdup(strtab +\
		ifswap32(((struct nlist_64 *)symtab)->n_un.n_strx, file.reverse)));
}


int								overlaps_symtab_command64(\
		struct symtab_command *sym)
{
	uint32_t					symbol_table_size;

	symbol_table_size = sym->nsyms * sizeof(struct nlist_64);
	if ((sym->symoff + symbol_table_size > sym->stroff
		&& sym->symoff < sym->stroff)
			|| (sym->stroff + sym->strsize > symbol_table_size
				&& sym->stroff < sym->symoff))
		return (1);
	else
		return (0);
}
