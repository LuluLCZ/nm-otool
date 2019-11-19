/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:28:53 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/26 13:40:01 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

char	*remove_char(char *str, char c)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	j = 0;
	dst = ft_strnew(ft_strlen(str));
	while (str[++i])
	{
		if (str[i] == c)
		{
			dst[j] = ' ';
			while (str[i + 1] == c)
				i++;
			j++;
		}
		else
		{
			dst[j] = str[i];
			j++;
		}
	}
	dst[j] = '\0';
	free(str);
	return (dst);
}
