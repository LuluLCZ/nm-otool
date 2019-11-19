/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:18:16 by Lulu              #+#    #+#             */
/*   Updated: 2017/12/12 14:06:28 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(s);
	i = 0;
	if ((char)c == '\0')
		return ((char *)s + j);
	while (i < j)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
