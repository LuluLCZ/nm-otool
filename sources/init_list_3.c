/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:15:06 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 14:15:16 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

t_info				*refresh_symbol(t_info *symbol)
{
	t_info			*tmp1;

	tmp1 = symbol;
	symbol = symbol->next;
	if (!(symbol = (t_info *)malloc(sizeof(t_info) * 128)))
	{
		ft_putstr("PB MALLOC");
		return (NULL);
	}
	symbol->prev = tmp1;
	symbol->next = NULL;
	symbol->n_type = 0;
	symbol->name_not_found = false;
	symbol->symbol_letter = ' ';
	symbol->symname = NULL;
	symbol->n_sect = 0;
	symbol->value = NULL;
	return (symbol);
}

t_mysects			*refresh_mysect(t_mysects *sections)
{
	t_mysects		*tmp;

	tmp = sections;
	sections = sections->next;
	if (!(sections = (t_mysects *)malloc(sizeof(t_mysects) * 128)))
		return (NULL);
	sections->prev = tmp;
	sections->next = NULL;
	sections->name = NULL;
	sections->index = 0;
	sections->address = 0;
	return (sections);
}

t_mysects_32		*refresh_mysect_32(t_mysects_32 *sections)
{
	t_mysects_32	*tmp;

	tmp = sections;
	sections = sections->next;
	if (!(sections = (t_mysects_32 *)malloc(sizeof(t_mysects_32) * 128)))
		return (NULL);
	sections->prev = tmp;
	sections->next = NULL;
	sections->name = NULL;
	sections->index = 0;
	sections->address = 0;
	return (sections);
}

t_mysects_32		*go_begin_32(t_mysects_32 *sections)
{
	t_mysects_32	*tmp;

	while (sections && sections->prev)
	{
		tmp = sections;
		sections = sections->prev;
		sections->next = tmp;
		tmp = NULL;
	}
	return (sections);
}
