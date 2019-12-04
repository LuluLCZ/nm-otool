/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:37:55 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/04 17:20:17 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft.h"
#include <stdbool.h>

typedef struct			s_info
{
	uint8_t				n_type;
	uint32_t			n_sect;
	bool				name_not_found;
	char				*symname;
	char				symbol_letter;
	char				*value;
	struct s_info		*next;
	struct s_info		*prev;
}						t_info;

typedef struct			s_mysects
{
	char				*name;
	uint64_t			index;
	uint64_t			address;
	uint64_t			size;
	struct s_mysects	*next;
	struct s_mysects	*prev;
}						t_mysects;

t_mysects				*init_mysect(void);
t_mysects				*refresh_mysect(t_mysects *sections);
t_mysects				*go_begin(t_mysects *sections);
t_info					*go_begin_info(t_info *data);
void					free_mysects(t_mysects *sections);
t_mysects				*go_end_mysects(t_mysects *sections);
t_info					*init_mysymbol(void);
t_info					*refresh_symbol(t_info *symbol);
t_info					*ft_swap_double(t_info *s1, t_info *s2, t_info **finfo);
void					handle_64(char *ptr, void *header);
t_info					*sort_names(t_info *data);
void					ft_putnbr_base(size_t n, size_t base, char *str);
char					global_case_symbol(uint8_t n_type, char c);
t_mysects				*find_section_from_nsect(t_mysects *sections, uint32_t nsect);
char					check_for_section(t_info *data, t_mysects *sections);
char					get_symbol_letter(t_info *data, t_mysects *sections);
char					*ft_str_lowerchar(char *str);
char					*adding_0(char *str);
void					handle_32(char *ptr, void *header);
char					*adding_0_32(char *str);
