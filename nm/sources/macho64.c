/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:07:02 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/07 04:04:36 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void parse_mach_64_symtab(struct symtab_command *sym, char *ptr, t_mysects *sections, t_info *data)
{
	uint32_t			i;
	void		*strtab;
	void		*symtab;
	// char		*zero = (char *)malloc(sizeof(char *) + 52);

	i = 0;
	strtab = (void *)ptr + sym->stroff;
	symtab = (void *)ptr + sym->symoff;
	while (i < sym->nsyms)
	{
		data->symname = ft_strdup(strtab + ((struct nlist_64 *)symtab)->n_un.n_strx);
		if (ft_strlen(data->symname) == 0) data->name_not_found = true;
		else data->name_not_found = false;
		data->n_type = ((struct nlist_64 *)symtab)->n_type;
		data->n_sect = ((struct nlist_64 *)symtab)->n_sect;
		data->symbol_letter = get_symbol_letter(data, sections);
		data->value = (char *)malloc(sizeof(char *) * 256);
		ft_putnbr_base(((struct nlist_64 *)symtab)->n_value, 16, data->value);
		data->value = adding_0(data->value, (data->symbol_letter == 'T') ? 1 : 0, 64);
		// if (data->name_not_found == false && !(N_STAB & data->n_type)) printf("%s %c %s\n", data->value, data->symbol_letter, data->symname);
		data = refresh_symbol(data);
		symtab += sizeof(struct nlist_64);
		i++;
	}
	data = sort_names(data);
	data = go_begin_info(data);
	while (data->next)
	{
		if (data->name_not_found == false && !(N_STAB & data->n_type))
		{
			ft_putstr(data->value);
			ft_putchar(' ');
			ft_putchar(data->symbol_letter);
			ft_putchar(' ');
			ft_putendl(data->symname);
			if (data->symbol_letter == 'I')
			{
				ft_putstr(" (indirect for ");
				ft_putstr(data->symname);
				ft_putendl(")");
			}
		}
		data = data->next;
	}
}

t_mysects	*parse_mach_64_segment(void *sc, t_mysects *sections)
{
	void					*section;
	uint32_t				nsects;
	uint32_t				i;

	section = sc + sizeof(struct segment_command_64);
	nsects = ((struct segment_command_64 *)sc)->nsects;
	i = 0;
	while (i < nsects)
	{
		sections->address = ((struct section_64 *)section)->addr;
		sections->index = sections->prev ? sections->prev->index + 1 : 1;
		sections->name = ft_strdup(((struct section_64 *)section)->sectname);
		sections->size = ((struct section_64 *)section)->size;
		sections = refresh_mysect(sections);
		section = section + sizeof(struct section_64);
		i++;
	}
	return (sections);
}

void	parse_load_command(struct load_command *lc)
{
	uint32_t	cmd;

	cmd = lc->cmd;
	if (cmd == LC_SEGMENT) puts("SEGMENT");
	if (cmd == LC_SYMTAB) puts("SYMTAB");
}

void handle_64(char *ptr, void *header)
{
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;
	struct segment_command_64 *sc;
	struct symtab_command *sym;
	t_mysects				*sections;
	t_info					*data;

	sections = init_mysect();
	ncmds = ((struct mach_header_64 *)header)->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	data = init_mysymbol();
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			parse_mach_64_symtab(sym, ptr, sections, data);
			// break;
		}
		else if (lc->cmd == LC_SEGMENT_64)
		{
			// puts("SEGMENT 64");
			sc = (struct segment_command_64 *)lc;
			sections = parse_mach_64_segment(sc, sections);
		}
		else if (lc->cmd == LC_SEGMENT)
			puts("SEGMENT");
		lc = (void *) lc + lc->cmdsize;
		i++;
	}
}