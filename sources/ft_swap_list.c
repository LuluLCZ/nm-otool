/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:52:30 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/03 16:21:25 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void		ft_norm_swap(t_info *s1, t_info *s2, t_info *first, t_info *last)
{
	while (first->next != s1 && first->next != NULL)
				first = first->next;
		if (first->next != NULL)
		{
				s1->prev = s2;
				s2->prev = first;
				last = s2->next;
				last->prev = s1;
				first->next = s2;
				s1->next = last;
				s2->next = s1;
		}
}

t_info		*ft_swap_double(t_info *s1, t_info *s2, t_info **finfo)
{
	t_info	*first;
	t_info	*last;

	first = *finfo;
	last = NULL;
	if (*finfo == s1)
	{
		*finfo = s2;
		last = s2->next;
		s1->next = last;
		s2->next = s1;
		s1->prev = s2;
		s2->prev = NULL;
		last->prev = s1;
	}
	else
		ft_norm_swap(s1, s2, first, last);
	return (*finfo);
}