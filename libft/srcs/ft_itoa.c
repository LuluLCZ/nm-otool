/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 00:54:37 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/23 13:36:53 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "../includes/libft.h"
#include <stdio.h>
#include <unistd.h>

static int	ft_lenght(int n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_newstringnb(int len, int n, int neg, char *nb)
{
	while (len >= 0)
	{
		nb[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	if (neg < 0)
		nb[0] = '-';
	return (nb);
}

char		*ft_itoa(int n)
{
	char	*nb;
	int		neg;
	int		len;

	len = ft_lenght(n);
	neg = n;
	if (!(nb = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	nb[len] = '\0';
	len--;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		nb[0] = 0;
	if (n < 0)
		n = -n;
	return (ft_newstringnb(len, n, neg, nb));
}
