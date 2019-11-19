/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:47:03 by Lulu              #+#    #+#             */
/*   Updated: 2017/12/12 14:08:01 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(s);
	i = 0;
	if ((char)c == '\0')
		return ((char *)s + j);
	while (j > 0)
	{
		if (s[j] == (char)c)
			return ((char *)s + j);
		j--;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}
