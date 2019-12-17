/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:37:55 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/17 18:00:29 by llacaze          ###   ########.fr       */
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
#include "../libft/includes/libft.h"
#include <stdbool.h>

# define BIN_OTOOL "ft_otool"
# define BIN_NM "ft_nm"

typedef struct			s_info
{
	uint32_t				n_type;
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
	uint32_t			offset;
	struct s_mysects	*next;
	struct s_mysects	*prev;
}						t_mysects;

typedef struct			s_mysects_32
{
	char				*name;
	uint32_t			index;
	uint32_t			address;
	uint32_t			size;
	struct s_mysects_32	*next;
	struct s_mysects_32	*prev;
}						t_mysects_32;

typedef struct			s_file
{
	char				*filename;
	uint32_t			size;
	void				*ptr;
	int					reverse;
	char				*bin;
}						t_file;

t_mysects				*init_mysect(void);
t_mysects				*refresh_mysect(t_mysects *sections);
t_mysects				*go_begin(t_mysects *sections);
t_mysects				*go_end_mysects(t_mysects *sections);
t_mysects_32				*init_mysect_32(void);
t_mysects_32				*refresh_mysect_32(t_mysects_32 *sections);
t_mysects_32				*go_begin_32(t_mysects_32 *sections);
t_mysects_32				*go_end_mysects_32(t_mysects_32 *sections);
t_info					*go_begin_info(t_info *data);
void					free_mysects(t_mysects *sections);
t_info					*init_mysymbol(void);
t_info					*refresh_symbol(t_info *symbol);
t_info					*ft_swap_double(t_info *s1, t_info *s2, t_info **finfo);
int						handle_64(void *header, t_file file);
t_info					*sort_names(t_info *data);
void					ft_putnbr_base(size_t n, size_t base, char *str);
char					global_case_symbol(uint8_t n_type, char c);
t_mysects				*find_section_from_nsect(t_mysects *sections, uint32_t nsect);
char					check_for_section(t_info *data, t_mysects *sections);
char					get_symbol_letter(t_info *data, t_mysects *sections, uint64_t value);
char					*ft_str_lowerchar(char *str);
char					*adding_0(char *str, char symbolAlpha, int process, char *symname);
int						handle_32(void *header, t_file file);
char					*adding_0_32(char *str);
void					check_file(t_file file);
int						handle_fat_32(struct fat_header *header, t_file file);
uint32_t				ft_swap_int32(uint32_t x);
uint64_t				ft_swap_int64(uint64_t x);
uint64_t				ifswap64(uint64_t x, int reverse);
uint32_t				ifswap32(uint32_t x, int reverse);
int						error_64_1(uint32_t index, uint64_t size, int i, t_file file);
int						error_64_2(uint32_t ncmds, t_file file, int i, uint32_t index, uint32_t cmdsize);
int						error_64_3(struct load_command *lc, t_file file, uint32_t index, void *header);
int						error_64_SEG_1(struct segment_command_64 *sc, struct load_command *lc, uint32_t index, t_file file);
int						overlaps_symtab_command64(struct symtab_command *sym);
int						error_64_SYM(struct symtab_command *sym, t_file file);
int						handle_64_symtab(struct load_command *lc, t_info *data, t_file file, t_mysects *sections);
void					print_64_data(t_info *data);
char					*check_string_64(void *symtab, t_file file, struct symtab_command *sym);
int						error_1(uint32_t index, uint64_t size, int i, t_file file);
int						error_2(uint32_t ncmds, t_file file, int i, uint32_t index, uint32_t cmdsize);
int						error_3(struct load_command *lc, t_file file, uint32_t index, void *header);
int						error_SEG_1(struct segment_command *sc, struct load_command *lc, uint32_t index, t_file file);
int						overlaps_symtab_command(struct symtab_command *sym);
int						error_SYM(struct symtab_command *sym, t_file file);
int						handle_symtab(struct load_command *lc, t_info *data, t_file file, t_mysects *sections);
void					print_data(t_info *data);
char					*check_string(void *symtab, t_file file, struct symtab_command *sym);
t_mysects				*parse_mach_64_segment(void *sc, t_mysects *sections, t_file file);
t_mysects				*parse_mach_32_segment(void *sc, t_mysects *sections, t_file file);
void					parse_mach_64_symtab(struct symtab_command *sym, t_file file, t_mysects *sections, t_info *data);
void					parse_mach_32_symtab(struct symtab_command *sym, t_file file, t_mysects *sections, t_info *data);
int						check_bad_string(char *str, t_file file);
int						error_SYMOFF(struct symtab_command *sym, t_file file, uint32_t i);
void					ft_putnbr_base_otool(size_t n, size_t base, char *str);
int						init_env(char *filename, t_file file);
