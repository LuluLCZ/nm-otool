/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:25:38 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:25:48 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int						print_arch_extends(t_file file,\
struct fat_arch *fat_arch)
{
	ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains\
	/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
	ft_putstr_fd(file.filename, 2);
	ft_putstr_fd(" truncated or malformed fat file (offset plus size \
	of cputype (", 2);
	ft_putnbr_fd(ifswap32(fat_arch->cputype, file.reverse), 2);
	ft_putstr_fd(") cpusubtype (", 2);
	ft_putnbr_fd(ifswap32(fat_arch->cpusubtype, file.reverse), 2);
	ft_putendl_fd(") extends past the end of the file)\n", 2);
	return (-1);
}

int						print_unaligned_offset(t_file file,\
struct fat_arch *fat_arch)
{
	ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains\
	/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
	ft_putstr_fd(file.filename, 2);
	ft_putstr_fd(" truncated or malformed fat file (offset: ", 2);
	ft_putnbr_fd(ifswap32(fat_arch->offset, file.reverse), 2);
	ft_putstr_fd(" for cputype (", 2);
	ft_putnbr_fd(ifswap32(fat_arch->cputype, file.reverse), 2);
	ft_putstr_fd(") cpusubtype (", 2);
	ft_putnbr_fd(ifswap32(fat_arch->cpusubtype, file.reverse), 2);
	ft_putendl_fd(") not aligned on it's alignment (2^12))\n", 2);
	return (-1);
}

int						check_for_error_in_offset(t_file file,\
struct fat_header *header, struct fat_arch *fat_arch)
{
	uint32_t			i;

	i = 0;
	while (i < ifswap32(header->nfat_arch, file.reverse))
	{
		if (ifswap32(fat_arch->size, file.reverse) + ifswap32(fat_arch->offset,\
		file.reverse) > file.size)
			return (print_arch_extends(file, fat_arch));
		if (ifswap32(fat_arch->offset, file.reverse) % 4096 != 0)
			return (print_unaligned_offset(file, fat_arch));
		fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		i++;
	}
	return (0);
}

int						check_fat_arch_32(struct fat_arch *fat_arch,\
struct fat_header *header, t_file file)
{
	if (check_for_error_in_arch(ifswap32(header->nfat_arch,\
	file.reverse), fat_arch, file) == -1)
		return (-1);
	if (check_for_error_in_offset(file, header, fat_arch) == -1)
		return (-1);
	if (check_for_host_arch(ifswap32(header->nfat_arch, file.reverse),\
	fat_arch, file) == 1)
		return (1);
	return (0);
}

int						handle_fat_32(\
struct fat_header *header, t_file file)
{
	uint32_t			i;
	struct fat_arch		*fat_arch;

	i = 0;
	fat_arch = (void *)file.ptr + sizeof(struct fat_header);
	if (check_fat_arch_32(fat_arch, header, file) != 0)
		return (-1);
	while (i < ifswap32(header->nfat_arch, file.reverse))
	{
		ft_putstr("\n");
		if (!ft_strcmp(file.bin, BIN_NM))
		{
			ft_putstr(file.filename);
			ft_putstr(" (for architecture ");
			ft_putstr(get_arch_type((int)(ifswap32(fat_arch->cputype,\
			file.reverse)),\
			(int)(ifswap32(fat_arch->cpusubtype, file.reverse))));
			ft_putstr("):\n");
		}
		check_file((t_file){file.filename, file.size, (void *)file.ptr +\
		ifswap32(fat_arch->offset, file.reverse), file.reverse, file.bin});
		fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		i++;
	}
	return (1);
}
