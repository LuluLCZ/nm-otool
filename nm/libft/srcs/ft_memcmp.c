/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:23:04 by Lulu              #+#    #+#             */
/*   Updated: 2017/12/12 14:05:38 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s12;
	unsigned char	*s22;

	i = 0;
	s12 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	while (i < n)
	{
		if (s12[i] != s22[i])
			return (s12[i] - s22[i]);
		i++;
	}
	return (0);
}
