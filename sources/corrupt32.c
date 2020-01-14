/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrupt32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:22:13 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 13:51:22 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int			error_3(struct load_command *lc, t_file file,\
		uint32_t index, void *header)
{
	if ((void *)lc + ifswap32(lc->cmdsize, file.reverse) >= (void *)file.ptr\
			+ file.size || (void *)lc < (void *)file.ptr)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains\
		/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (load command ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" extends past end of file)\n", 2);
		return (-1);
	}
	if ((void *)lc + (lc->cmdsize || 1) > (void *)header +\
	sizeof(struct mach_header) + ((struct mach_header *)header)->sizeofcmds)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/\
		XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (load command ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" extends past the end all load commands in the \
		file)\n", 2);
		return (-1);
	}
	return (0);
}

int			error_sym(struct symtab_command *sym, t_file file)
{
	if (overlaps_symtab_command(sym) == 1)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains\
		/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object \
		(string table at offset ", 2);
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
