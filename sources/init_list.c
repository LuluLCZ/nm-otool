/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:22:39 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 14:15:04 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

t_mysects			*init_mysect(void)
{
	t_mysects		*sections;

	if (!(sections = (t_mysects *)malloc(sizeof(t_mysects))))
		return (NULL);
	sections->prev = NULL;
	sections->next = NULL;
	sections->name = NULL;
	sections->index = 0;
	sections->address = 0;
	return (sections);
}

t_mysects_32		*init_mysect_32(void)
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

t_info				*init_mysymbol(void)
{
	t_info			*symbol;

	if (!(symbol = (t_info *)malloc(sizeof(t_info))))
	{
		ft_putstr("PB MALLOC");
		return (NULL);
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

t_info				*go_end_info(t_info *info)
{
	while (info && info->next)
		info = info->next;
	return (info);
}
