/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:51:32 by llacaze           #+#    #+#             */
/*   Updated: 2019/12/17 19:22:31 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"
#include "libft.h"


uint32_t	ifswap32(uint32_t x, int reverse)
{
	if (reverse == 1)
		return (ft_swap_int32(x));
	return (x);
}

uint64_t	ifswap64(uint64_t x, int reverse)
{
	if (reverse == 1)
		return (ft_swap_int64(x));
	return (x);
}

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
		if (sections->index == nsect) return sections;
		sections = sections->next;
	}
	return (NULL);
}

char	check_for_section(t_info *data, t_mysects *sections)
{
	t_mysects	*right_sect;

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
	return '?';
}

char	get_symbol_letter(t_info *data, t_mysects *sections, uint64_t value)
{
	if ((N_TYPE & data->n_type) == N_SECT)
		return check_for_section(data, sections);
	else if (N_STAB & data->n_type)
		return '-';
	else if ((N_TYPE & data->n_type) == N_UNDF)
	{
		if (value == 0)
			return 'U';
		else if (data->n_type & N_EXT && ((data->n_type & N_TYPE) == N_UNDF))
			return 'C';
		else
			return '?';
	}
	else if ((N_TYPE & data->n_type) == N_ABS)
		return (global_case_symbol(data->n_type, 'A'));
	else if ((N_TYPE & data->n_type) == N_INDR)
		return (global_case_symbol(data->n_type, 'I'));
	return '?';
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

char		*adding_0(char *str, char symbolAlpha, int process, char *symname)
{
	uint32_t		i;
	char	*dump;
	char	*tmp;

	i = 0;
	if (ft_strlen(str) == 1 || symbolAlpha == 'I' || symbolAlpha == 'U')
	{
		free(str);
		if ((ft_strcmp(symname, "r") == 0 && ft_strlen(symname) == 1) || (ft_strcmp(symname, "bad string index") == 0 && ft_strlen(symname) == 16) || symbolAlpha == 'T' || symbolAlpha == '?')
			return (ft_strdup((process == 64) ? ("0000000000000000") : ("00000000")));
		return (ft_strdup((process == 64) ? ("                ") : ("        ")));
	}
	dump = ft_memalloc(17);
	while (i < ((process == 64) ? 16 : 8) - ft_strlen(str))
	{
		dump[i] = '0';
		i++;
	}
	dump[i] = '\0';
	tmp = ft_str_lowerchar(ft_strjoin_free(dump, str));
	return (tmp);
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
			if (ft_strcmp(data->symname, data->next->symname) > 0 || (ft_strcmp(data->symname, data->next->symname) == 0 && ft_strcmp(&data->symbol_letter, &data->next->symbol_letter) > 0 && data->symbol_letter != '?') ||\
			(ft_strcmp(data->symname, data->next->symname) == 0 && ft_strcmp(&data->symbol_letter, &data->next->symbol_letter) == 0 && ft_strcmp(data->value, data->next->value) > 0))
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

void			check_file(t_file file)
{
	uint32_t	magic_number;
	void			*header;

	magic_number = *(uint32_t *)file.ptr;
	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		// puts("32");
		header = (struct mach_header *)file.ptr;
		file.reverse = (magic_number == MH_CIGAM) ? 1 : 0;
		handle_32(header, file);
	}
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		// puts("64");
		header = (struct mach_header_64 *)file.ptr;
		file.reverse = (magic_number == MH_CIGAM_64) ? 1 : 0;
		handle_64(header, file);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		header = (struct fat_header *)file.ptr;
		file.reverse = (magic_number == FAT_CIGAM) ? 1 : 0;
		handle_fat_32(header, file);
	}
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
	{
		header = (struct fat_header_64 *)file.ptr;
	}
	else
	{
		puts("The file was not recognized as a valid object file");
	}
}

int init_env(char *filename, t_file file)
{
	int fd;
	struct stat buf;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if ((fstat(fd, &buf)) < 0)
	{
		perror("fstat");
		return (EXIT_FAILURE);
	}
	file.filename = ft_strdup(filename);
	file.size = buf.st_size;
	if ((file.ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	check_file(file);
	free(file.filename);
	if (munmap(file.ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}