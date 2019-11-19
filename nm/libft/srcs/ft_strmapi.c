/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 20:23:37 by llacaze           #+#    #+#             */
/*   Updated: 2017/12/12 14:07:33 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s2;
	int		i;

	i = 0;
	if (s && f)
	{
		if (!(s2 = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1))))
			return (NULL);
		while (s[i])
		{
			s2[i] = f(i, s[i]);
			i++;
		}
		s2[i] = '\0';
		return (s2);
	}
	return (NULL);
}
