/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 13:41:14 by Lulu              #+#    #+#             */
/*   Updated: 2017/12/12 14:07:21 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	end_dst;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	end_dst = i;
	if (size == 0)
		return (end_dst + ft_strlen(src));
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (end_dst < size)
		dst[i] = '\0';
	return (end_dst + ft_strlen(src));
}
