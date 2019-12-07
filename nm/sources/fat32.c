/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:02:58 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/07 04:14:31 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

char		*get_arch_type(int cputype, int cpusubtype)
{
	if (cputype == CPU_TYPE_I386)
		return ("i386");
	else if (cputype == CPU_TYPE_X86_64)
		return ("x86_64");
	else if (cputype == CPU_TYPE_ARM)
	{
		if (cpusubtype == CPU_SUBTYPE_ARM_V6)
			return ("armv6");
		else if (cpusubtype == CPU_SUBTYPE_ARM_V7)
			return ("armv7");
		else if (cpusubtype == CPU_SUBTYPE_ARM_V7S)
			return ("armv7s");
		else if (cpusubtype == CPU_SUBTYPE_ARM_V8)
			return ("armv8");
		else
			return ("arm");
	}
	else if (cputype == CPU_TYPE_ARM64)
		return ("arm64");
	else if (cputype == CPU_TYPE_POWERPC)
	{
		if (cpusubtype == CPU_SUBTYPE_POWERPC_7400)
			return ("ppc_7400");
		else
			return ("ppc");
	}
	else
		return ("");
}

uint32_t	ft_swap_int32(uint32_t x)
{
	uint32_t tmp1;
	uint32_t tmp2;
	uint32_t tmp3;
	uint32_t tmp4;

	tmp1 = (x & 0xFF000000) >> 24;
	tmp2 = (x & 0x000000FF) << 24;
	tmp3 = (x & 0x00FF0000) >> 8;
	tmp4 = (x & 0x0000FF00) << 8;
	return (tmp1 | tmp2 | tmp3 | tmp4);
}

uint64_t	ft_swap_int64(uint64_t x)
{
	uint64_t	tmp1;
	uint64_t	tmp2;
	uint64_t	tmp3;
	uint64_t	tmp4;
	uint64_t	tmp5;
	uint64_t	tmp6;
	uint64_t	tmp7;
	uint64_t	tmp8;

	tmp1 = (x & 0xFF00000000000000) >> 56;
	tmp2 = (x & 0x00000000000000FF) << 56;
	tmp3 = (x & 0x00FF000000000000) >> 40;
	tmp4 = (x & 0x000000000000FF00) << 40;
	tmp5 = (x & 0x0000FF0000000000) >> 24;
	tmp6 = (x & 0x0000000000FF0000) << 24;
	tmp7 = (x & 0x000000FF00000000) >> 8;
	tmp8 = (x & 0x00000000FF000000) << 8;
	return (tmp1 | tmp2 | tmp3 | tmp4 | tmp5 | tmp6 | tmp7 | tmp8);
}

int		check_for_error_in_arch(uint32_t nfat_arch, struct fat_arch *fat_arch, char *filename)
{
	uint32_t	i;

	i = 0;
	while (i < nfat_arch)
	{
		if (fat_arch->offset == 0 && fat_arch->cputype == 0 && fat_arch->cpusubtype == 0)
		{
			ft_putstr("./ft_nm: ");
			ft_putstr(filename);
			ft_putendl(" truncated or malformed fat file (cputype (0) cpusubtype (0) offset 0 overlaps universal headers)\n");
			return (1);
		}
		fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		i++;
	}
	return (0);
}

int			check_for_host_arch(uint32_t nfat_arch, struct fat_arch *fat_arch, int reverse, void *ptr)
{
	uint32_t	i;

	i = 0;
	while (i < nfat_arch)
	{
		if (ifswap32(fat_arch->cputype, reverse) == CPU_TYPE_X86_64)
		{
			nm((void *)ptr + ft_swap_int32(fat_arch->offset), NULL);
			return (1);
		}
		fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		i++;
	}
	return (0);
}


int			handle_fat_32(char *ptr, struct fat_header *header, char *filename, int reverse)
{
	uint32_t				i;
	struct fat_arch	*fat_arch;

	i = 0;
	fat_arch = (void *)ptr + sizeof(struct fat_header);
	if (check_for_error_in_arch(ifswap32(header->nfat_arch, reverse), fat_arch, filename) == 1)
		return (-1);
	if (check_for_host_arch(ifswap32(header->nfat_arch, reverse), fat_arch, reverse, ptr) == 1)
		return (1);
	while (i < ifswap32(header->nfat_arch, reverse))
	{
		ft_putstr("\n");
		ft_putstr(filename);
		ft_putstr(" (for architecture ");
		ft_putstr(get_arch_type((int)(ifswap32(fat_arch->cputype, reverse)), (int)(ifswap32(fat_arch->cpusubtype, reverse))));
		ft_putstr("):\n");
		nm((void *)ptr + ifswap32(fat_arch->offset, reverse), filename);
		fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		i++;
	}
	return (1);
}