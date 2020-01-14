/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:54:08 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 17:10:00 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void							otool_print_64(t_file file, t_mysects *sections)
{
	ft_putstr(file.filename);
	if (!ft_strcmp(sections->name, SECT_TEXT))
	{
		ft_putstr(":\nContents of (__TEXT,__text) section\n");
		first_hexdump_64(sections->size, \
		(void *)file.ptr + sections->offset, sections->address, file);
	}
	free_sections(sections);
}

t_mysects						*parse_mach_64_segment(void *sc,\
	t_mysects *sections, t_file file)
{
	void						*section;
	uint32_t					i;

	section = sc + sizeof(struct segment_command_64);
	i = 0;
	while (i < ifswap64(\
	((struct segment_command_64 *)sc)->nsects, file.reverse))
	{
		if (error_64_1(i, ifswap64(((struct section_64 *)section)->size,\
			file.reverse), 0, file) == -1)
		{
			free_sections(sections);
			return (NULL);
		}
		sections = f_sect_64((struct section_64 *)section, file, sections);
		if (!ft_strcmp(file.bin, BIN_OTOOL))
		{
			otool_print_64(file, sections);
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
	if (error_64_2(ncmds, file, -1, 0) == -1)
		return (-1);
	while (i < ncmds)
	{
		if (error_64_3(lc, file, i, header) == -1)
			return (-1);
		if (error_64_2(ncmds, file, i,\
			ifswap32(lc->cmdsize, file.reverse)) == -1)
			return (-1);
		if (ifswap32(lc->cmd, file.reverse) == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64 *)lc;
			if (error_64_seg_1(sc, i, file) == -1)
				return (-1);
		}
		lc = (void *)lc + ifswap32(lc->cmdsize, file.reverse);
		i++;
	}
	return (0);
}
