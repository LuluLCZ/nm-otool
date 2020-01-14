/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:52:55 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:53:03 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

char							hex_digit(int v)
{
	if (v >= 0 && v < 10)
		return ('0' + v);
	else
		return ('a' + v - 10);
}

void							print_address_hex(void *p0)
{
	int							i;
	uintptr_t					p;

	p = (uintptr_t)p0;
	ft_putstr("0x");
	i = (sizeof(p) << 2) - 4;
	while (i >= 0)
	{
		i -= 4;
		ft_putchar(hex_digit((p >> i) & 0xf));
	}
}

void							free_sections(t_mysects *sections)
{
	t_mysects					*tmp;

	sections = go_begin(sections);
	while (sections)
	{
		if (sections->next)
			tmp = sections->next;
		free(sections->name);
		if (sections->next)
		{
			free(sections);
			sections = tmp;
			tmp = NULL;
		}
		else
			break ;
	}
	free(sections);
}

void							ft_putnbr_base_otool(\
size_t n, size_t base, char *str)
{
	if (base == 10)
		ft_putnbr(n);
	else if (n < 0)
		ft_putchar('0');
	else
	{
		if (n <= 15)
			str[ft_strlen(str)] = '0';
		if (n >= base)
			ft_putnbr_base(n / base, base, str);
		if (n % base < 10)
			str[ft_strlen(str)] = ((n % base) + 48);
		else
			str[ft_strlen(str)] = ((n % base) - 10 + 65);
	}
}

int								check_bad_string(char *str, t_file file)
{
	int							i;

	if ((void *)str >= file.ptr + file.size || (void *)str < file.ptr)
		return (-1);
	i = 0;
	while ((void *)str + i < file.ptr + file.size - 1 && str[i])
		i++;
	if (str[i])
		return (i);
	return (0);
}
