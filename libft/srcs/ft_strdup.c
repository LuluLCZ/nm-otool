/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:50:25 by Lulu              #+#    #+#             */
/*   Updated: 2019/12/13 15:23:12 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(char) * ft_strlen(src) + 2)))
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup_free(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(char) * ft_strlen(src) + 1)))
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	free(src);
	return (dest);
}


char	*ft_strdup_size(char *src, int n)
{
	char		*dest;
	int		i;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(char) * (n + 2) + 1)))
		return (NULL);
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	// printf("%c -> c,", src[i]);
	dest[i] = src[i];
	dest[i + 1] = '\0';
	return (dest);
}