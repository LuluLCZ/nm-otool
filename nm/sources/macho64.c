/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mama <mama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:07:02 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/12 16:10:19 by mama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"


char	*ft_strdup_access(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if (src == NULL)
		return ("");
	if (!(dest = (char *)malloc(sizeof(char) * ft_strlen(src) + 1)))
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_bad_string(char *str, t_file file)
{
	if ((void *)str >= file.ptr + file.size || (void *)str < file.ptr)
		return (-1);
	return (0);
}

void parse_mach_64_symtab(struct symtab_command *sym, t_file file, t_mysects *sections, t_info *data, int reverse)
{
	uint32_t			i;
	void		*strtab;
	void		*symtab;

	i = 0;
	strtab = (void *)file.ptr + ifswap32(sym->stroff, reverse);
	symtab = (void *)file.ptr + ifswap32(sym->symoff, reverse);
	// printf("%d -> reverse -> mach32sym\n", reverse);
	while (i < ifswap32(sym->nsyms, reverse))
	{
		printf("%s -> symname\n", strtab + ifswap64(((struct nlist_64 *)symtab)->n_un.n_strx, reverse));
		if (check_bad_string(strtab + ifswap64(((struct nlist_64 *)symtab)->n_un.n_strx, reverse), file) == -1)
			data->symname = ft_strdup("bad index string");
		else
			data->symname = ft_strdup(strtab + ifswap64(((struct nlist_64 *)symtab)->n_un.n_strx, reverse));
		if (ft_strlen(data->symname) == 0) data->name_not_found = true;
		else data->name_not_found = false;
		data->n_type = ((struct nlist_64 *)symtab)->n_type;
		data->n_sect = ((struct nlist_64 *)symtab)->n_sect;
		data->symbol_letter = get_symbol_letter(data, sections);
		data->value = (char *)malloc(sizeof(char *) * 256);
		ft_putnbr_base(ifswap64(((struct nlist_64 *)symtab)->n_value, reverse), 16, data->value);
		data->value = adding_0(data->value, data->symbol_letter == 'T' ? 1 : 0, 64);
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
			if (data->symbol_letter == 'I')
			{
				ft_putstr(data->symname);
				ft_putstr(" (indirect for ");
				ft_strcmp(data->symname, "bad index string") == 0 ? ft_putstr("?") : ft_putstr(data->symname);
				ft_putendl(")");
			}
			else
			{
				ft_putendl(data->symname);
			}
			
		}
		data = data->next;
	}
}

t_mysects	*parse_mach_64_segment(void *sc, t_mysects *sections, int reverse, t_file file)
{
	void					*section;
	uint32_t				nsects;
	uint32_t				i;

	section = sc + sizeof(struct segment_command_64);
	nsects = ifswap64(((struct segment_command_64 *)sc)->nsects, reverse);
	i = 0;
	while (i < nsects)
	{
		if (ifswap64(((struct section_64 *)section)->size, reverse) > file.size)
		{
			ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
			ft_putstr_fd(file.filename, 2);
			ft_putstr_fd(" truncated or malformed object (offset field plus size field of section ", 2);
			ft_putnbr_fd(i, 2);
			ft_putendl_fd(" in LC_SEGMENT_64 command 1 extends past the end of the file)\n", 2);
			return (NULL);
		}
		sections->address = ifswap64(((struct section_64 *)section)->addr, reverse);
		sections->index = sections->prev ? sections->prev->index + 1 : 1;
		sections->name = ft_strdup(((struct section_64 *)section)->sectname);
		sections->size = ifswap64(((struct section_64 *)section)->size, reverse);
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

int	check_load_command_64(t_file file, int reverse, void *header, struct load_command *lc, uint32_t ncmds)
{
	uint32_t i;
	struct segment_command_64 *sc;

	i = 0;
	if (ncmds == 0)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: error: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putendl_fd(" The file was not recognized as a valid object file\n", 2);
		return (-1);
	}
	while (i < ncmds)
	{
		if ((void *)lc + ifswap32(lc->cmdsize, reverse) >= (void *)file.ptr + file.size || (void *)lc < (void *)file.ptr)
		{
			ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
			ft_putstr_fd(file.filename, 2);
			ft_putstr_fd(" truncated or malformed object (load command ", 2);
			ft_putnbr_fd(i, 2);
			ft_putendl_fd(" extends past end of file)\n", 2);
			return (-1);
		}
		if ((void *)lc + (lc->cmdsize || 1) > (void *)header + sizeof(struct mach_header_64) + ((struct mach_header_64 *)header)->sizeofcmds)
		{
			ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
			ft_putstr_fd(file.filename, 2);
			ft_putstr_fd(" truncated or malformed object (load command ", 2);
			ft_putnbr_fd(i, 2);
			ft_putendl_fd(" extends past the end all load commands in the file)\n", 2);
			return (-1);
		}
		if (ifswap64(((struct mach_header_64 *)header)->sizeofcmds, reverse) > file.size)
		{
			ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
			ft_putstr_fd(file.filename, 2);
			ft_putendl_fd(" truncated or malformed object (load commands extend past the end of the file)\n", 2);
			return (-1);
		}
		if (ifswap32(lc->cmdsize, reverse) > file.size)
		{
			ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
			ft_putstr_fd(file.filename, 2);
			ft_putstr_fd(" truncated or malformed object (load command ", 2);
			ft_putnbr_fd(i, 2);
			ft_putendl_fd(" extends past end of file)\n", 2);
			return (-1);
		}
		else if (ifswap64(lc->cmd, reverse) == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64 *)lc;
			if (ifswap32(lc->cmdsize, reverse) != sizeof(*sc) + sizeof(struct section_64) * ((struct segment_command_64 *)sc)->nsects)
			{
				ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
				ft_putstr_fd(file.filename, 2);
				ft_putstr_fd("truncated or malformed object (load command ", 2);
				ft_putnbr_fd(i, 2);
				ft_putendl_fd(" inconsistent cmdsize in LC_SEGMENT_64 for the number of sections)\n", 2);
				return (-1);
			}
			if (file.size < ifswap64(sc->fileoff, reverse) + ifswap64(sc->filesize, reverse))
			{
				ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
				ft_putstr_fd(file.filename, 2);
				ft_putstr_fd(" truncated or malformed object (load command ", 2);
				ft_putnbr_fd(i, 2);
				ft_putendl_fd(" fileoff field plus filesize field in LC_SEGMENT_64 extends past the end of the file)\n", 2);
				return (-1);
			}
		}
		lc = (void *) lc + ifswap32(lc->cmdsize, reverse);
		i++;
	}
	return (0);
}

int	 handle_64(void *header, int reverse, t_file file)
{
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;
	struct segment_command_64 *sc;
	struct symtab_command *sym;
	t_mysects				*sections;
	t_info					*data;

	sections = init_mysect();
	ncmds = ifswap64(((struct mach_header_64 *)header)->ncmds, reverse);
	i = 0;
	lc = (void *)file.ptr + sizeof(struct mach_header_64);
	data = init_mysymbol();
	if (check_load_command_64(file, reverse, header, lc, ncmds) == -1)
		return (-1);
	while (i < ncmds)
	{
		if (ifswap32(lc->cmd, reverse) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			parse_mach_64_symtab(sym, file, sections, data, reverse);
		}
		else if (ifswap32(lc->cmd, reverse) == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64 *)lc;
			if ((sections = parse_mach_64_segment(sc, sections, reverse, file)) == NULL)
				return (-1);
		}
		lc = (void *) lc + ifswap32(lc->cmdsize, reverse);
		i++;
	}
	return (0);
}