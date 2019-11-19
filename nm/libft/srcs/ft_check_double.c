/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:50:25 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 17:04:44 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

char	*norm_check(char *str, char *new)
{
	int		i;
	int		j;
	int		a;

	i = 0;
	while (str[i])
	{
		a = i;
		j = -1;
		while (new[++j])
			if (str[i] == new[j])
			{
				i++;
				break ;
			}
		if (a == i)
		{
			new[j] = str[i];
			i++;
		}
	}
	free(str);
	return (new);
}

char	*ft_check_double(char *str)
{
	char	*new;

	new = ft_strnew(ft_strlen(str));
	new = norm_check(str, new);
	new[ft_strlen(new)] = '\0';
	return (new);
}

char	*retry(char *str)
{
	char *new;
	char *new_str;

	new = ft_check_double(str);
	new_str = ft_strdup_free(new);
	return (new_str);
}
