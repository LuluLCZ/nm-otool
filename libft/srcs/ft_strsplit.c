/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 08:26:00 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/14 17:06:31 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		j;
	int			start;
	int			end;

	tab = NULL;
	j = 0;
	i = 0;
	if (s && (tab = (char **)malloc(sizeof(char *) * ft_strlen(s))))
	{
		while (s[i] != '\0')
		{
			while (s[i] == c && s[i] != '\0')
				i++;
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			end = i;
			if (end > start)
				tab[j++] = ft_strsub(s, start, (end - start));
		}
		tab[j] = NULL;
	}
	return (tab);
}
