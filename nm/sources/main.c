/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:51:32 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/04 17:25:53 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"
#include "libft.h"

void	ft_putnbr_base(size_t n, size_t base, char *str)
{
	if (base == 10)
		ft_putnbr(n);
	else if (n < 0)
		ft_putchar('0');
	else
	{
		if (n >= base)
			ft_putnbr_base(n / base, base, str);
		if (n % base < 10)
			str[ft_strlen(str)] = ((n % base) + 48);
		else
			str[ft_strlen(str)] = ((n % base) - 10 + 65);
	}
}

char		global_case_symbol(uint8_t n_type, char c)
{
	if (!(n_type & N_EXT))
		return (ft_tolower(c));
	else
		return (c);
}

t_mysects	*find_section_from_nsect(t_mysects *sections, uint32_t nsect)
{
	sections = go_begin(sections);
	while (sections)
	{
		// printf("%llu -> index, %u -> nsect", sections->index, nsect);
		if (sections->index == nsect) return sections;
		sections = sections->next;
	}
	return (NULL);
}

char	check_for_section(t_info *data, t_mysects *sections)
{
	t_mysects	*right_sect;

	// printf("%llu -> data->n_sect", data->n_sect);
	if ((right_sect = find_section_from_nsect(sections, data->n_sect)))
	{
		if (!right_sect->name)
		{
			return (global_case_symbol(data->n_type, 'S'));
		}
		// printf("|%d|", (bool)(ft_strcmp(right_sect->name, SECT_DATA)));
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
		// if (!(data->n_type & N_EXT))
			// return (data->n_type - 'A' - 'a');
	}
	return '-';
}

char	get_symbol_letter(t_info *data, t_mysects *sections)
{
	if ((N_TYPE & data->n_type) == N_SECT)
		return check_for_section(data, sections);
	else if (N_STAB & data->n_type)
		return '-';
	else if ((N_TYPE & data->n_type) == N_UNDF)
	{
		if (data->name_not_found)
			return 'C';
		else if (data->n_type & N_EXT)
			return 'U';
		else
			return '?';
	}
	 //For the moment we don't have sections so we'll just put S
		// return (match_symbol_section(saved_sections, data));
	else if ((N_TYPE & data->n_type) == N_ABS)
		return (global_case_symbol(data->n_type, 'A'));
	else if ((N_TYPE & data->n_type) == N_INDR)
		return (global_case_symbol(data->n_type, 'I'));
	return ' ';
}

char		*ft_str_lowerchar(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

char		*adding_0(char *str)
{
	int		i;
	char	*dump;

	dump = ft_strnew(32);
	i = 0;
	while (i < 16 - ft_strlen(str))
	{
		dump[i] = '0';
		i++;
	}
	dump[i] = '\0';
	if (ft_strlen(str) == 1) return ("                ");
	return (ft_str_lowerchar(ft_strjoin(dump, str)));
}

char		*adding_0_32(char *str)
{
	int		i;
	char	*dump;

	dump = ft_strnew(32);
	i = 0;
	while (i < 8 - ft_strlen(str))
	{
		dump[i] = '0';
		i++;
	}
	dump[i] = '\0';
	if (ft_strlen(str) == 1) return ("        ");
	return (ft_str_lowerchar(ft_strjoin(dump, str)));
}

t_info		*sort_names(t_info *data)
{
	t_info *head;

	data = go_begin_info(data);
	head = data;
	if (data->next->symname != NULL && data->symname != NULL && data->next->next != NULL)
	{
		while (data->next->next)
		{
			if (ft_strcmp(data->symname, data->next->symname) > 0)
			{
				data = ft_swap_double(data, data->next, &head);
				data = go_begin_info(data);
			}
			else
				data = data->next;
		}
	}
	return data;
}

void nm(char *ptr)
{
	unsigned int	magic_number;
	void			*header;

	magic_number = *(int *) ptr;
	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		// puts("Binaire pour 32-bits");
		header = (struct mach_header *)ptr;
		handle_32(ptr, header);
	}
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		// puts("Binaire pour 64-bits");
		header = (struct mach_header *)ptr;
		handle_64(ptr, header);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		puts("Binaire fat 32-bits");
		header = (struct fat_header *)ptr;
	}
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
	{
		puts("Binaire fat 64-bits");
		header = (struct fat_header_64 *)ptr;
	}
	else
	{
		puts("The file was not recognized as a valid object file");
	}
}

int main(int ac, char **av)
{
	int fd;
	char *ptr;
	struct stat buf;

	if (ac != 2)
	{
		fprintf(stderr, "give args");
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if ((fstat(fd, &buf)) < 0)
	{
		perror("fstat");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}