/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:43:48 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/26 13:40:47 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

void		free_tab_o(char **str)
{
	int		i;

	i = -1;
	while (str[++i + 1] != NULL)
		free(str[i]);
	free(str[i]);
	free(str);
}

void		free_tab(char **str)
{
	int		i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

char		**copy_tab_o(char **tmp)
{
	int		i;
	char	**env;

	i = -1;
	if (!(env = (char **)malloc(sizeof(char *) * 20480)))
		return (NULL);
	while (tmp[++i])
		env[i] = ft_strdup(tmp[i]);
	env[i] = NULL;
	return (env);
}

char		**copy_tab(char **env, char **oenv)
{
	int		i;

	i = -1;
	if (!(env = (char **)malloc(sizeof(char *) * 2048)))
		return (NULL);
	while (oenv[++i])
		env[i] = ft_strdup(oenv[i]);
	env[i] = NULL;
	return (env);
}

char		**alloc_tab(int size)
{
	char	**tab;

	if (!(tab = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	return (tab);
}
