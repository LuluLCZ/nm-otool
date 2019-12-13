/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:22:39 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/13 20:07:59 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

t_mysects	*init_mysect(void)
{
	t_mysects	*sections;

	if (!(sections = (t_mysects *)malloc(sizeof(t_mysects))))
		return (NULL);
	sections->prev = NULL;
	sections->next = NULL;
	sections->name = NULL;
	sections->index = 0;
	sections->address = 0;
	return (sections);
}

t_mysects_32	*init_mysect_32(void)
{
	t_mysects_32	*sections;

	if (!(sections = (t_mysects_32 *)malloc(sizeof(t_mysects_32))))
		return (NULL);
	sections->prev = NULL;
	sections->next = NULL;
	sections->name = NULL;
	sections->index = 0;
	sections->address = 0;
	return (sections);
}

t_info		*init_mysymbol(void)
{
	t_info	*symbol;

	if (!(symbol = (t_info *)malloc(sizeof(t_info))))
	{
		ft_putstr("PB MALLOC");
		return NULL;
	}
	symbol->next = NULL;
	symbol->prev = NULL;
	symbol->n_type = 0;
	symbol->name_not_found = false;
	symbol->symbol_letter = ' ';
	symbol->symname = NULL;
	symbol->n_sect = 0;
	symbol->value = NULL;
	return (symbol);
}

t_info			*go_end_info(t_info *info)
{
	while (info && info->next) info = info->next;
	return info;
}

t_info		*refresh_symbol(t_info *symbol)
{
	t_info		*tmp1;

	tmp1 = symbol;
	symbol = symbol->next;
	if (!(symbol = (t_info *)malloc(sizeof(t_info) * 128)))
	{
		ft_putstr("PB MALLOC");
		return NULL;
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

t_mysects	*refresh_mysect(t_mysects *sections)
{
	t_mysects	*tmp;

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

t_mysects_32	*refresh_mysect_32(t_mysects_32 *sections)
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

t_mysects_32	*go_begin_32(t_mysects_32 *sections)
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

t_mysects	*go_begin(t_mysects *sections)
{
	t_mysects	*tmp;

	while (sections && sections->prev)
	{
		tmp = sections;
		sections = sections->prev;
		sections->next = tmp;
		tmp = NULL;
	}
	return (sections);
}

t_info		*go_begin_info(t_info *data)
{
	t_info	*tmp;

	while (data && data->prev)
	{
		tmp = data;
		data = data->prev;
		data->next = tmp;
		tmp = NULL;
	}
	return (data);
}

t_mysects		*go_end_mysects(t_mysects *sections)
{
	while (sections && sections->next) sections = sections->next;
	return sections;
}




t_mysects_32		*go_end_mysects_32(t_mysects_32 *sections)
{
	while (sections && sections->next) sections = sections->next;
	return sections;
}

void		free_mysects(t_mysects *sections)
{
	if (sections->name)
		free(sections->name);
}