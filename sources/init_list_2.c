/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:14:37 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 14:14:48 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

t_mysects			*go_begin(t_mysects *sections)
{
	t_mysects		*tmp;

	while (sections && sections->prev)
	{
		tmp = sections;
		sections = sections->prev;
		sections->next = tmp;
		tmp = NULL;
	}
	return (sections);
}

t_info				*go_begin_info(t_info *data)
{
	t_info			*tmp;

	while (data && data->prev)
	{
		tmp = data;
		data = data->prev;
		data->next = tmp;
		tmp = NULL;
	}
	return (data);
}

t_mysects			*go_end_mysects(t_mysects *sections)
{
	while (sections && sections->next)
		sections = sections->next;
	return (sections);
}

t_mysects_32		*go_end_mysects_32(t_mysects_32 *sections)
{
	while (sections && sections->next)
		sections = sections->next;
	return (sections);
}

void				free_mysects(t_mysects *sections)
{
	if (sections->name)
		free(sections->name);
}
