/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:22:59 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/17 18:06:12 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_nm.h"

int			main(int ac, char **av)
{
	int		i;
	t_file	file;

	i = 1;
	file.bin = ft_strdup(BIN_OTOOL);
	while (i < ac)
	{
		init_env(av[i], file);
		i++;
	}
	return (0);
}