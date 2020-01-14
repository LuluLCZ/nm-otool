/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:26:13 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:26:22 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

uint64_t				ft_swap_int64(uint64_t x)
{
	return (ft_swap_int64_1(x) | ft_swap_int64_2(x));
}

int						print_unaligned(t_file file, struct fat_arch *fat_arch)
{
	ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/\
	XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
	ft_putstr_fd(file.filename, 2);
	ft_putstr_fd(" truncated or malformed fat file (align: 2^", 2);
	ft_putnbr_fd(ifswap32(fat_arch->align, file.reverse), 2);
	ft_putstr_fd(" for cputype (", 2);
	ft_putnbr_fd(ifswap32(fat_arch->cputype, file.reverse), 2);
	ft_putstr_fd(") cpusubtype (", 2);
	ft_putnbr_fd(ifswap32(fat_arch->cpusubtype, file.reverse), 2);
	ft_putendl_fd(") (maximum 2^15))\n", 2);
	ft_putnbr_fd(file.reverse, 2);
	return (-1);
}

int						print_overlaps(t_file file, struct fat_arch *fat_arch)
{
	ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains\
	/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
	ft_putstr_fd(file.filename, 2);
	ft_putstr_fd(" truncated or malformed fat file (cputype (", 2);
	ft_putnbr_fd(fat_arch->cputype, 2);
	ft_putstr_fd(") cpusubtype (", 2);
	ft_putnbr_fd(fat_arch->cpusubtype, 2);
	ft_putstr_fd(") offset ", 2);
	ft_putnbr_fd(fat_arch->offset, 2);
	ft_putendl_fd(" overlaps universal headers)\n", 2);
	return (-1);
}

int						check_for_error_in_arch(uint32_t nfat_arch,\
struct fat_arch *fat_arch, t_file file)
{
	uint32_t			i;

	i = 0;
	if (ifswap32(fat_arch->align, file.reverse) > 32768)
		return (print_unaligned(file, fat_arch));
	while (i < nfat_arch)
	{
		if (fat_arch->offset == 0 && fat_arch->cputype == 0 &&\
		fat_arch->cpusubtype == 0)
			return (print_overlaps(file, fat_arch));
		fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		i++;
	}
	return (0);
}

int						check_for_host_arch(uint32_t nfat_arch,\
struct fat_arch *fat_arch, t_file file)
{
	uint32_t			i;

	i = 0;
	while (i < nfat_arch)
	{
		if (ifswap32(fat_arch->cputype, file.reverse) == CPU_TYPE_X86_64)
		{
			check_file((t_file){file.filename, file.size, (void *)file.ptr +\
			ifswap32(fat_arch->offset, file.reverse), file.reverse, file.bin});
			return (1);
		}
		fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		i++;
	}
	return (0);
}
