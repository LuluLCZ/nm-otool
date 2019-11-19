/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 00:19:14 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/14 18:37:17 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../includes/libft.h"

char			*ft_strjoin_free(char *s1, char *s2)
{
	char			*str;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (s1)
		i = ft_strlen(s1);
	if (s2)
		j = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	ft_memcpy(str, s1, i);
	ft_memcpy(str + i, s2, j);
	str[i + j] = '\0';
	free(s2);
	return (str);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (s1)
		i = ft_strlen(s1);
	if (s2)
		j = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	ft_memcpy(str, s1, i);
	ft_memcpy(str + i, s2, j);
	str[i + j] = '\0';
	return (str);
}
