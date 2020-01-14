/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:51:32 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 15:49:34 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"
#include "libft.h"

void				macho32(t_file file, uint32_t magic_number)
{
	void			*header;

	header = (struct mach_header *)file.ptr;
	file.reverse = (magic_number == MH_CIGAM) ? 1 : 0;
	handle_32(header, file);
}

void				macho64(t_file file, uint32_t magic_number)
{
	void			*header;

	header = (struct mach_header_64 *)file.ptr;
	file.reverse = (magic_number == MH_CIGAM_64) ? 1 : 0;
	handle_64(header, file);
}

void				check_file(t_file file)
{
	uint32_t		magic_number;
	void			*header;

	magic_number = *(uint32_t *)file.ptr;
	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		macho32(file, magic_number);
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		macho64(file, magic_number);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		header = (struct fat_header *)file.ptr;
		file.reverse = (magic_number == FAT_CIGAM) ? 1 : 0;
		handle_fat_32(header, file);
	}
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
		header = (struct fat_header_64 *)file.ptr;
	else
		ft_putendl_fd("The file was not recognized as a valid object file", 2);
}

int					errors_on_file(int i, char *filename)
{
	if (i == 1)
	{
		ft_putstr_fd("Cannot open file ", 2);
		ft_putendl_fd(filename, 2);
		return (EXIT_FAILURE);
	}
	else if (i == 2)
	{
		ft_putstr_fd("Fstat error on file ", 2);
		ft_putendl_fd(filename, 2);
		return (EXIT_FAILURE);
	}
	return (0);
}

int					init_env(char *filename, t_file file)
{
	int				fd;
	struct stat		buf;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (errors_on_file(1, filename));
	if ((fstat(fd, &buf)) < 0)
		return (errors_on_file(2, filename));
	file.filename = ft_strdup(filename);
	file.size = buf.st_size;
	if ((file.ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))\
	== MAP_FAILED)
	{
		free(file.filename);
		ft_putendl_fd("Problem with mmap", 2);
		return (EXIT_FAILURE);
	}
	check_file(file);
	free(file.filename);
	if (munmap(file.ptr, buf.st_size) < 0)
	{
		ft_putendl_fd("Impossible to munmap ptr", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
