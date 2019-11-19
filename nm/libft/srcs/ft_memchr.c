/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:18:39 by Lulu              #+#    #+#             */
/*   Updated: 2017/12/12 14:05:36 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		c1;
	const char	*s1;

	s1 = s;
	i = 0;
	c1 = c;
	while (i < n)
	{
		if (s1[i] == c1)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
