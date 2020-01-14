/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho32_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:51:27 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:51:40 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

t_mysects						*f_sect(\
struct section *section, t_file file, t_mysects *sections)
{
	sections->address = ifswap32(\
	((struct section *)section)->addr, file.reverse);
	sections->offset = ifswap32(\
	((struct section *)section)->offset, file.reverse);
	sections->index = sections->prev ? sections->prev->index + 1 : 1;
	sections->name = ft_strdup(((struct section *)section)->sectname);
	sections->size = ifswap32(((struct section *)section)->size,\
	file.reverse);
	return (sections);
}

void							otool_print(t_file file, t_mysects *sections)
{
	ft_putstr(file.filename);
	if (!ft_strcmp(sections->name, SECT_TEXT))
	{
		ft_putstr(":\nContents of (__TEXT,__text) section\n");
		first_hexdump(sections->size, \
		(void *)file.ptr + sections->offset, sections->address, file);
	}
	free_sections(sections);
}

t_mysects						*parse_mach_32_segment(void *sc,\
	t_mysects *sections, t_file file)
{
	void						*section;
	uint32_t					i;

	section = sc + sizeof(struct segment_command);
	i = 0;
	while (i < ifswap32(\
	((struct segment_command *)sc)->nsects, file.reverse))
	{
		if (error_1(i, ifswap32(((struct section *)section)->size,\
			file.reverse), 0, file) == -1)
		{
			free_sections(sections);
			return (NULL);
		}
		sections = f_sect((struct section *)section, file, sections);
		if (!ft_strcmp(file.bin, BIN_OTOOL))
		{
			otool_print(file, sections);
			return (NULL);
		}
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
	struct segment_command		*sc;

	i = 0;
	if (error_2(ncmds, file, -1, 0) == -1)
		return (-1);
	while (i < ncmds)
	{
		if (error_3(lc, file, i, header) == -1)
			return (-1);
		if (error_2(ncmds, file, i,\
			ifswap32(lc->cmdsize, file.reverse)) == -1)
			return (-1);
		if (ifswap32(lc->cmd, file.reverse) == LC_SEGMENT)
		{
			sc = (struct segment_command *)lc;
			if (error_seg_1(sc, lc, i, file) == -1)
				return (-1);
		}
		lc = (void *)lc + ifswap32(lc->cmdsize, file.reverse);
		i++;
	}
	return (0);
}
