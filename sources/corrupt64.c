/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrupt64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 21:19:47 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/16 17:10:02 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int		error_64_1(uint32_t index, uint64_t size, int i, t_file file)
{
	if (i == 0 && size > file.size)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (offset field plus size field of section ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" in LC_SEGMENT_64 command 1 extends past the end of the file)\n", 2);
		return (-1);
	}
	return (0);
}

int		error_64_2(uint32_t ncmds, t_file file, int i, uint32_t index, uint32_t cmdsize)
{
	if (ncmds == 0 && i == 0)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: error: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putendl_fd(" The file was not recognized as a valid object file\n", 2);
		return (-1);
	}
	if (cmdsize == 0 && i == 1)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (load command ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" extends past end of file)\n", 2);
		return (-1);
	}
	return (0);
}

int		error_64_SEG_1(struct segment_command_64 *sc, struct load_command *lc, uint32_t index, t_file file)
{
	if (ifswap32(lc->cmdsize, file.reverse) != sizeof(*sc) + sizeof(struct section_64) * ifswap32(((struct segment_command_64 *)sc)->nsects, file.reverse))
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (load command ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" inconsistent cmdsize in LC_SEGMENT_64 for the number of sections)\n", 2);
		return (-1);
	}
	if (file.size < ifswap64(sc->fileoff, file.reverse) + ifswap64(sc->filesize, file.reverse))
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (load command ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" fileoff field plus filesize field in LC_SEGMENT_64 extends past the end of the file)\n", 2);
		return (-1);
	}
	return (0);
}

int		error_64_3(struct load_command *lc, t_file file, uint32_t index, void *header)
{
	if ((void *)lc + ifswap32(lc->cmdsize, file.reverse) >= (void *)file.ptr + file.size || (void *)lc < (void *)file.ptr)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (load command ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" extends past end of file)\n", 2);
		return (-1);
	}
	if ((void *)lc + (lc->cmdsize || 1) > (void *)header + sizeof(struct mach_header_64) + ((struct mach_header_64 *)header)->sizeofcmds)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (load command ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" extends past the end all load commands in the file)\n", 2);
		return (-1);
	}
	return (0);
}

int		error_64_SYM(struct symtab_command *sym, t_file file)
{
	if (overlaps_symtab_command64(sym) == 1)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (string table at offset ", 2);
		ft_putnbr_fd(sym->stroff, 2);
		ft_putstr_fd(" with a size of ", 2);
		ft_putnbr_fd(sym->strsize, 2);
		ft_putstr_fd(", overlaps symbol table at offset ", 2);
		ft_putnbr_fd(sym->symoff, 2);
		ft_putstr_fd(" with a size of ", 2);
		ft_putnbr_fd((sym->nsyms * sizeof(struct nlist_64)), 2);
		ft_putendl_fd(")\n", 2);
		return (-1);
	}
	return (0);
}