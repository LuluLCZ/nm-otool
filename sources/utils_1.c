/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:31:19 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:40:55 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

uint32_t			ifswap32(uint32_t x, int reverse)
{
	if (reverse == 1)
		return (ft_swap_int32(x));
	return (x);
}

uint64_t			ifswap64(uint64_t x, int reverse)
{
	if (reverse == 1)
		return (ft_swap_int64(x));
	return (x);
}

void				ft_putnbr_base(size_t n, size_t base, char *str)
{
	if (base == 10)
		ft_putnbr(n);
	else if (n < 0)
		ft_putchar('0');
	else
	{
		if (n >= base)
			ft_putnbr_base(n / base, base, str);
		if (n % base < 10)
			str[ft_strlen(str)] = ((n % base) + 48);
		else
			str[ft_strlen(str)] = ((n % base) - 10 + 65);
	}
}

char				global_case_symbol(uint8_t n_type, char c)
{
	if (!(n_type & N_EXT))
		return (ft_tolower(c));
	else
		return (c);
}

t_mysects			*find_section_from_nsect(t_mysects *sections,\
uint32_t nsect)
{
	sections = go_begin(sections);
	while (sections)
	{
		if (sections->index == nsect)
			return (sections);
		sections = sections->next;
	}
	return (NULL);
}
