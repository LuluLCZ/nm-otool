/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:07:02 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 17:08:44 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void							free_info(t_info *data)
{
	t_info						*tmp;

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

int								lc_symtab_handle(\
uint32_t i, t_mysects *sections, t_file file, struct load_command *lc)
{
	struct symtab_command		*sym;
	t_info						*data;

	data = init_mysymbol();
	if (ifswap32(lc->cmd, file.reverse) == LC_SYMTAB)
	{
		printf("oefkwowkfwe\n");
		sym = (struct symtab_command *)lc;
		if (error_64_sym(sym, file) == -1 ||\
		error_symoff(sym, file, i) == -1 || error_64_stroff(sym, file, i) == -1)
			return (-1);
		parse_mach_64_symtab(sym, file, sections, data);
	}
	free_info(data);
	return (0);
}

t_mysects						*handle_seg_64(\
struct load_command *lc, t_mysects *sections, t_file file)
{
	struct segment_command_64	*sc;

	if (ifswap32(lc->cmd, file.reverse) == LC_SEGMENT_64)
	{
		sc = (struct segment_command_64 *)lc;
		return (parse_mach_64_segment(sc, sections, file));
	}
	return (sections);
}

int								handle_64(void *header, t_file file)
{
	uint32_t					i;
	struct load_command			*lc;
	t_mysects					*sections;

	i = 0;
	lc = (void *)file.ptr + sizeof(struct mach_header_64);
	if (check_load_command_64(file, header, lc, ifswap64(\
	((struct mach_header_64 *)header)->ncmds, file.reverse)) == -1)
		return (-1);
	sections = init_mysect();
	while (i < ifswap64(((struct mach_header_64 *)header)->ncmds, file.reverse))
	{
		if (lc_symtab_handle(\
			i, sections, file, (struct load_command *)lc) == -1)
			break ;
		if ((sections = \
		handle_seg_64((struct load_command *)lc, sections, file)) == NULL)
			break ;
		lc = (void *)lc + ifswap32(lc->cmdsize, file.reverse);
		i++;
	}
	free_sections(sections);
	return (0);
}
