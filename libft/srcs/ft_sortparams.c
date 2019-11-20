/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortparams.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:53:42 by llacaze           #+#    #+#             */
/*   Updated: 2017/12/12 14:06:21 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

void	disp(char **av)
{
	int		nb;

	nb = 1;
	while (av[nb])
	{
		ft_putstr(av[nb]);
		ft_putchar('\n');
		nb++;
	}
}

void	ft_sortparams(int ac, char **av)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = 0;
	if (ac <= 1)
		exit(EXIT_FAILURE);
	while (av[i + 1] != '\0')
	{
		if (ft_strcmp(av[i], av[i + 1]) > 0)
		{
			tmp = av[i + 1];
			av[i + 1] = av[i];
			av[i] = tmp;
			i = 0;
		}
		i++;
	}
	i = 1;
	disp(av);
}
