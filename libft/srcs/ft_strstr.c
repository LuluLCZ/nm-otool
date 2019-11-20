/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 13:29:29 by Lulu              #+#    #+#             */
/*   Updated: 2017/12/12 14:08:06 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	size_t	j;
	int		a;

	i = 0;
	if (needle[i] == '\0')
		return ((void *)haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		a = i;
		while (haystack[i + j] == needle[j])
		{
			j++;
			if (needle[j] == '\0')
				return ((void *)haystack + a);
		}
		a = 0;
		i++;
	}
	return (NULL);
}
