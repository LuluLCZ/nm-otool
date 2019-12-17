/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:43:50 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/17 19:15:56 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_nm.h"

int			main(int ac, char **av)
{
	int		i;
	t_file	file;

	i = 1;
	file.bin = ft_strdup(BIN_NM);
	while (i < ac)
	{
		init_env(av[i], file);
		i++;
	}
	free(file.bin);
	return (0);
}