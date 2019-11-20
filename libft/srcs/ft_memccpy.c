/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:27:10 by llacaze           #+#    #+#             */
/*   Updated: 2017/12/12 14:05:32 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst2;
	char			*src2;
	char			c2;
	size_t			i;

	i = 0;
	c2 = c;
	dst2 = (void *)dst;
	src2 = (void *)src;
	while (i < n)
	{
		dst2[i] = src2[i];
		if (src2[i] == c2)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
