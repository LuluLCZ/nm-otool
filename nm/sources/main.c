/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:51:32 by llacaze           #+#    #+#             */
/*   Updated: 2019/11/18 17:37:41 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int i;
	char *stringtable;
	struct nlist_64 *el;

	i = 0;
	el = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	while (i < nsyms)
	{
		ft_putstr(stringtable + el[i].n_un.n_strx);
		ft_putchar('\n');
		i++;
	}
}

void handle_64(char *ptr)
{
	int ncmds;
	int i;
	struct mach_header_64 *header;
	struct load_command *lc;
	struct symtab_command *sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == 0x2)
		{
			sym = (struct symtab_command *)lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (void *) lc + lc->cmdsize;
		i++;
	}
}

void nm(char *ptr)
{
	int magic_number;

	magic_number = *(int *) ptr;
	if (magic_number == MH_MAGIC)
	{
		puts("Binaire pour 32-bits");
	}
	if (magic_number == MH_MAGIC_64)
	{
		puts("Binaire pour 64-bits");
		handle_64(ptr);
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