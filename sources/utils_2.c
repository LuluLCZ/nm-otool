/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:32:25 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:50:04 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

t_info				*sort_names(t_info *data)
{
	t_info			*head;

	data = go_begin_info(data);
	head = data;
	if (data->next->symname != NULL && data->symname != NULL\
	&& data->next->next != NULL)
	{
		while (data->next->next)
		{
			if (ft_strcmp(data->symname, data->next->symname) > 0 ||\
(ft_strcmp(data->symname, data->next->symname) == 0 &&\
ft_strcmp(&data->symbol_letter, &data->next->symbol_letter) > 0 &&
			data->symbol_letter != '?') ||\
			(ft_strcmp(data->symname, data->next->symname) == 0 &&\
ft_strcmp(&data->symbol_letter, &data->next->symbol_letter) == 0 &&\
ft_strcmp(data->value, data->next->value) > 0))
			{
				data = ft_swap_double(data, data->next, &head);
				data = go_begin_info(data);
			}
			else
				data = data->next;
		}
	}
	return (data);
}

char				check_for_section(t_info *data, t_mysects *sections)
{
	t_mysects		*right_sect;

	if ((right_sect = find_section_from_nsect(sections, data->n_sect)))
	{
		if (!right_sect->name)
			return (global_case_symbol(data->n_type, 'S'));
		if (!ft_strcmp(right_sect->name, SECT_TEXT))
			return (global_case_symbol(data->n_type, 'T'));
		else if (!ft_strcmp(right_sect->name, SECT_DATA))
			return (global_case_symbol(data->n_type, 'D'));
		else if (!ft_strcmp(right_sect->name, SECT_BSS))
			return (global_case_symbol(data->n_type, 'B'));
		else if (!ft_strcmp(right_sect->name, SECT_COMMON))
			return (global_case_symbol(data->n_type, 'S'));
		else
			return (global_case_symbol(data->n_type, 'S'));
	}
	return ('?');
}

char				get_symbol_letter(t_info *data, t_mysects *sections,\
uint64_t value)
{
	if ((N_TYPE & data->n_type) == N_SECT)
		return (check_for_section(data, sections));
	else if (N_STAB & data->n_type)
		return ('-');
	else if ((N_TYPE & data->n_type) == N_UNDF)
	{
		if (value == 0)
			return ('U');
		else if (data->n_type & N_EXT && ((data->n_type & N_TYPE) == N_UNDF))
			return ('C');
		else
			return ('?');
	}
	else if ((N_TYPE & data->n_type) == N_ABS)
		return (global_case_symbol(data->n_type, 'A'));
	else if ((N_TYPE & data->n_type) == N_INDR)
		return (global_case_symbol(data->n_type, 'I'));
	return ('?');
}

char				*ft_str_lowerchar(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

char				*adding_0(char *str, char al, int pcs,\
char *symname)
{
	uint32_t		i;
	char			*dump;
	char			*tmp;

	i = 0;
	if (ft_strlen(str) == 1 || al == 'I' || al == 'U')
	{
		free(str);
		if ((ft_strcmp(symname, "r") == 0 && ft_strlen(symname) == 1) ||\
		(ft_strcmp(symname, "bad string index") == 0 &&\
		ft_strlen(symname) == 16) || al == 'T' || al == '?')
			return (ft_strdup(pcs == 64 ? ("0000000000000000") : ("00000000")));
		return (ft_strdup(pcs == 64 ? ("                ") : ("        ")));
	}
	dump = ft_memalloc(17);
	while (i < ((pcs == 64) ? 16 : 8) - ft_strlen(str))
	{
		dump[i] = '0';
		i++;
	}
	dump[i] = '\0';
	tmp = ft_str_lowerchar(ft_strjoin_free(dump, str));
	return (tmp);
}
