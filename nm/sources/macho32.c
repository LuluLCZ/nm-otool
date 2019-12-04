/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:43:59 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/04 17:21:03 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void parse_mach_32_symtab(struct symtab_command *sym, char *ptr, t_mysects *sections, t_info *data)
{
	uint32_t			i;
	void		*strtab;
	void		*symtab;
	char		*zero = (char *)malloc(sizeof(char *) + 52);

	i = 0;
	strtab = (void *)ptr + sym->stroff;
	symtab = (void *)ptr + sym->symoff;
	while (i < sym->nsyms)
	{
		data->symname = ft_strdup(strtab + ((struct nlist *)symtab)->n_un.n_strx);
		if (ft_strlen(data->symname) == 0) data->name_not_found = true;
		else data->name_not_found = false;
		data->n_type = ((struct nlist *)symtab)->n_type;
		data->n_sect = ((struct nlist *)symtab)->n_sect;
		data->symbol_letter = get_symbol_letter(data, sections);
		data->value = (char *)malloc(sizeof(char *) * 256);
		ft_putnbr_base(((struct nlist *)symtab)->n_value, 16, data->value);
		data->value = adding_0_32(data->value);
		// if (data->name_not_found == false && !(N_STAB & data->n_type)) printf("%s %c %s\n", data->value, data->symbol_letter, data->symname);
		data = refresh_symbol(data);
		symtab += sizeof(struct nlist);
		i++;
	}
	data = sort_names(data);
	data = go_begin_info(data);
	while (data->next)
	{
		if (data->name_not_found == false && !(N_STAB & data->n_type)) printf("%s %c %s\n", data->value, data->symbol_letter, data->symname);
		data = data->next;
	}
}

t_mysects	*parse_mach_32_segment(void *sc, t_mysects *sections)
{
	void					*section;
	uint32_t				nsects;
	uint32_t				i;

	section = sc + sizeof(struct segment_command);
	nsects = ((struct segment_command *)sc)->nsects;
	i = 0;
	while (i < nsects)
	{
		sections->address = ((struct section *)section)->addr;
		sections->index = sections->prev ? sections->prev->index + 1 : 1;
		sections->name = ft_strdup(((struct section *)section)->sectname);
		sections->size = ((struct section *)section)->size;
		// printf("name of section: %s, index of section: %llu, address of section: %llu, size of section: %llu\n", sections->name, sections->index, sections->address, sections->size);
		sections = refresh_mysect(sections);
		section = section + sizeof(struct section);
		i++;
	}
	return (sections);
}

// void	parse_load_command(struct load_command *lc)
// {
// 	uint32_t	cmd;

// 	cmd = lc->cmd;
// 	if (cmd == LC_SEGMENT) puts("SEGMENT");
// 	if (cmd == LC_SYMTAB) puts("SYMTAB");
// }

void handle_32(char *ptr, void *header)
{
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;
	struct segment_command *sc;
	struct symtab_command *sym;
	t_mysects				*sections;
	t_info					*data;

	sections = init_mysect();
	ncmds = ((struct mach_header *)header)->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(struct mach_header);
	data = init_mysymbol();
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			parse_mach_32_symtab(sym, ptr, sections, data);
			// break;
		}
		else if (lc->cmd == LC_SEGMENT_64)
		{
			puts("SEGMENT 64");
		}
		else if (lc->cmd == LC_SEGMENT)
		{
			sc = (struct segment_command *)lc;
			sections = parse_mach_32_segment(sc, sections);
		}
		lc = (void *) lc + lc->cmdsize;
		i++;
	}
}