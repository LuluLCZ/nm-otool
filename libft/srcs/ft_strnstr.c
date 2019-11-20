/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 13:57:45 by Lulu              #+#    #+#             */
/*   Updated: 2017/12/12 14:07:58 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	a;
	size_t	len2;

	len2 = len;
	i = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		len = len2;
		a = i;
		j = 0;
		while (s1[i + j] == s2[j] && i < len)
		{
			j++;
			if (s2[j] == '\0')
				return ((char *)s1 + a);
			len--;
		}
		a = 0;
		i++;
	}
	return (NULL);
}
