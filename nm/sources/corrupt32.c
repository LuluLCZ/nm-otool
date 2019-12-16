/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrupt32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:30:57 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/16 19:46:26 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int		error_1(uint32_t index, uint64_t size, int i, t_file file)
{
	if (i == 0 && size > file.size)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (offset field plus size field of section ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" in LC_SEGMENT command 1 extends past the end of the file)\n", 2);
		return (-1);
	}
	return (0);
}

int		error_2(uint32_t ncmds, t_file file, int i, uint32_t index, uint32_t cmdsize)
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

int		error_SEG_1(struct segment_command *sc, struct load_command *lc, uint32_t index, t_file file)
{
	if (ifswap32(lc->cmdsize, file.reverse) != sizeof(*sc) + sizeof(struct section) * ifswap32(((struct segment_command *)sc)->nsects, file.reverse))
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (load command ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" inconsistent cmdsize in LC_SEGMENT for the number of sections)\n", 2);
		return (-1);
	}
	if (file.size < ifswap32(sc->fileoff, file.reverse) + ifswap32(sc->filesize, file.reverse))
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (load command ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" fileoff field plus filesize field in LC_SEGMENT extends past the end of the file)\n", 2);
		return (-1);
	}
	return (0);
}

int		error_3(struct load_command *lc, t_file file, uint32_t index, void *header)
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
	if ((void *)lc + (lc->cmdsize || 1) > (void *)header + sizeof(struct mach_header) + ((struct mach_header *)header)->sizeofcmds)
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

int		error_SYM(struct symtab_command *sym, t_file file)
{
	if (overlaps_symtab_command(sym) == 1)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (string table at offset ", 2);
		ft_putnbr_fd(ifswap32(sym->stroff, file.reverse), 2);
		ft_putstr_fd(" with a size of ", 2);
		ft_putnbr_fd(ifswap32(sym->strsize, file.reverse), 2);
		ft_putstr_fd(", overlaps symbol table at offset ", 2);
		ft_putnbr_fd(ifswap32(sym->symoff, file.reverse), 2);
		ft_putstr_fd(" with a size of ", 2);
		ft_putnbr_fd((sym->nsyms * sizeof(struct nlist)), 2);
		ft_putendl_fd(")\n", 2);
		return (-1);
	}
	return (0);
}

int		error_SYMOFF(struct symtab_command *sym, t_file file, uint32_t i)
{
	(void)sym;
	(void)file;
	(void)i;
	// if (sym->symoff > file.size)
	// {
	// 	ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
	// 	ft_putstr_fd(file.filename, 2);
	// 	ft_putstr_fd(" truncated or malformed object (symoff field of LC_SYMTAB command ", 2);
	// 	ft_putnbr_fd(i, 2);
	// 	ft_putstr_fd(" extends past the end of the file", 2);
	// 	ft_putendl_fd(")\n", 2);
	// 	return (-1);
	// }
	return (0);
}