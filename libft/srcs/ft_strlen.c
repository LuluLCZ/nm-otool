/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 13:33:28 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/13 14:09:13 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/libft.h"

size_t	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	if (str != NULL)
		while (str[i])
			i++;
	return (i);
}
