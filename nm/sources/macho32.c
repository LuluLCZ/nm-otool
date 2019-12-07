/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:43:59 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/07 04:04:23 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void parse_mach_32_symtab(struct symtab_command *sym, char *ptr, t_mysects *sections, t_info *data, int reverse)
{
	uint32_t			i;
	void		*strtab;
	void		*symtab;

	i = 0;
	strtab = (void *)ptr + ifswap32(sym->stroff, reverse);
	symtab = (void *)ptr + ifswap32(sym->symoff, reverse);
	// printf("%d -> reverse -> mach32sym\n", reverse);
	while (i < ifswap32(sym->nsyms, reverse))
	{
		data->symname = ft_strdup(strtab + ifswap32(((struct nlist *)symtab)->n_un.n_strx, reverse));
		if (ft_strlen(data->symname) == 0) data->name_not_found = true;
		else data->name_not_found = false;
		data->n_type = ((struct nlist *)symtab)->n_type;
		data->n_sect = ((struct nlist *)symtab)->n_sect;
		data->symbol_letter = get_symbol_letter(data, sections);
		data->value = (char *)malloc(sizeof(char *) * 256);
		ft_putnbr_base(ifswap32(((struct nlist *)symtab)->n_value, reverse), 16, data->value);
		data->value = adding_0(data->value, data->symbol_letter == 'T' ? 1 : 0, 32);
		data = refresh_symbol(data);
		symtab += sizeof(struct nlist);
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

t_mysects	*parse_mach_32_segment(void *sc, t_mysects *sections, int reverse)
{
	void					*section;
	uint32_t				nsects;
	uint32_t				i;

	section = sc + sizeof(struct segment_command);
	nsects = ((reverse == 1) ? ft_swap_int32(((struct segment_command *)sc)->nsects) : ((struct segment_command *)sc)->nsects);
	i = 0;
	while (i < nsects)
	{
		sections->address = ifswap32(((struct section *)section)->addr, reverse);
		sections->index = sections->prev ? sections->prev->index + 1 : 1;
		sections->name = ft_strdup(((struct section *)section)->sectname);
		sections->size = ifswap32(((struct section *)section)->size, reverse);
		sections = refresh_mysect(sections);
		section = (void *)section + sizeof(struct section);
		i++;
	}
	return (sections);
}

void handle_32(void *ptr, void *header, int reverse)
{
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;
	struct segment_command *sc;
	struct symtab_command *sym;
	t_mysects				*sections;
	t_info					*data;

	sections = init_mysect();
	ncmds = ifswap32(((struct mach_header *)header)->ncmds, reverse);
	i = 0;
	lc = (struct load_command *)((void *)ptr + sizeof(struct mach_header));
	data = init_mysymbol();
	while (i < ncmds)
	{
		uint32_t cmd = ifswap32(lc->cmd, reverse);
		uint32_t cmdsize = ifswap32(lc->cmdsize, reverse);
		if (cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			parse_mach_32_symtab(sym, ptr, sections, data, reverse);
		}
		else if (cmd == LC_SEGMENT)
		{
			sc = (struct segment_command *)lc;
			sections = parse_mach_32_segment(sc, sections, reverse);
		}
		lc = (void *) lc + cmdsize;
		i++;
	}
}