/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:43:59 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:51:25 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int								lc_symtab_32_handle(\
uint32_t i, t_mysects *sections, t_file file, struct load_command *lc)
{
	struct symtab_command		*sym;
	t_info						*data;

	data = init_mysymbol();
	if (ifswap32(lc->cmd, file.reverse) == LC_SYMTAB)
	{
		sym = (struct symtab_command *)lc;
		if (error_sym(sym, file) == -1 ||\
		error_symoff(sym, file, i) == -1 || error_64_stroff(sym, file, i) == -1)
			return (-1);
		parse_mach_32_symtab(sym, file, sections, data);
	}
	free_info(data);
	return (0);
}

t_mysects						*handle_seg(\
struct load_command *lc, t_mysects *sections, t_file file)
{
	struct segment_command	*sc;

	if (ifswap32(lc->cmd, file.reverse) == LC_SEGMENT)
	{
		sc = (struct segment_command *)lc;
		return (parse_mach_32_segment(sc, sections, file));
	}
	return (sections);
}

int								handle_32(void *header, t_file file)
{
	uint32_t					i;
	struct load_command			*lc;
	t_mysects					*sections;

	i = 0;
	lc = (void *)file.ptr + sizeof(struct mach_header);
	if (check_load_command(file, header, lc, ifswap32(\
	((struct mach_header *)header)->ncmds, file.reverse)) == -1)
		return (-1);
	sections = init_mysect();
	while (i < ifswap32(((struct mach_header *)header)->ncmds, file.reverse))
	{
		if (lc_symtab_32_handle(\
			i, sections, file, (struct load_command *)lc) == -1)
			break ;
		if ((sections = \
		handle_seg((struct load_command *)lc, sections, file)) == NULL)
			break ;
		lc = (void *)lc + ifswap32(lc->cmdsize, file.reverse);
		i++;
	}
	free_sections(sections);
	return (0);
}
