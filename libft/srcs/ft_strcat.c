/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:25:01 by Lulu              #+#    #+#             */
/*   Updated: 2017/12/12 14:06:25 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../includes/libft.h"

char	*ft_strcat(char *base, const char *toadd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (base[i])
		i++;
	while (toadd[j] != '\0')
	{
		base[i] = toadd[j];
		i++;
		j++;
	}
	base[i] = '\0';
	return (base);
}
