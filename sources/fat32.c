/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:02:58 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:26:12 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

char					*ret_subtype(int cpusubtype)
{
	if (cpusubtype == CPU_SUBTYPE_ARM_V6)
		return ("armv6");
	else if (cpusubtype == CPU_SUBTYPE_ARM_V7)
		return ("armv7");
	else if (cpusubtype == CPU_SUBTYPE_ARM_V7S)
		return ("armv7s");
	else if (cpusubtype == CPU_SUBTYPE_ARM_V8)
		return ("armv8");
	return ("arm");
}

char					*get_arch_type(int cputype, int cpusubtype)
{
	if (cputype == CPU_TYPE_I386)
		return ("i386");
	else if (cputype == CPU_TYPE_X86_64)
		return ("x86_64");
	else if (cputype == CPU_TYPE_ARM)
		ret_subtype(cpusubtype);
	else if (cputype == CPU_TYPE_ARM64)
		return ("arm64");
	else if (cputype == CPU_TYPE_POWERPC)
	{
		if (cpusubtype == CPU_SUBTYPE_POWERPC_7400)
			return ("ppc_7400");
		else
			return ("ppc");
	}
	return ("");
}

uint32_t				ft_swap_int32(uint32_t x)
{
	uint32_t			tmp1;
	uint32_t			tmp2;
	uint32_t			tmp3;
	uint32_t			tmp4;

	tmp1 = (x & 0xFF000000) >> 24;
	tmp2 = (x & 0x000000FF) << 24;
	tmp3 = (x & 0x00FF0000) >> 8;
	tmp4 = (x & 0x0000FF00) << 8;
	return (tmp1 | tmp2 | tmp3 | tmp4);
}

uint64_t				ft_swap_int64_1(uint64_t x)
{
	uint64_t			tmp1;
	uint64_t			tmp2;
	uint64_t			tmp3;
	uint64_t			tmp4;

	tmp1 = (x & 0xFF00000000000000) >> 56;
	tmp2 = (x & 0x00000000000000FF) << 56;
	tmp3 = (x & 0x00FF000000000000) >> 40;
	tmp4 = (x & 0x000000000000FF00) << 40;
	return (tmp1 | tmp2 | tmp3 | tmp4);
}

uint64_t				ft_swap_int64_2(uint64_t x)
{
	uint64_t			tmp5;
	uint64_t			tmp6;
	uint64_t			tmp7;
	uint64_t			tmp8;

	tmp5 = (x & 0x0000FF0000000000) >> 24;
	tmp6 = (x & 0x0000000000FF0000) << 24;
	tmp7 = (x & 0x000000FF00000000) >> 8;
	tmp8 = (x & 0x00000000FF000000) << 8;
	return (tmp5 | tmp6 | tmp7 | tmp8);
}
