/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:51:32 by llacaze           #+#    #+#             */
/*   Updated: 2019/11/19 17:41:18 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"
#include "../libft/includes/libft.h"

void	ft_putnbr_base(size_t n, int base)
{
	if (base == 10)
		ft_putnbr(n);
	else if (n < 0)
		ft_putchar('0');
	else
	{
		if (n >= base)
			ft_putnbr_base(n / base, base);
		if (n % base < 10)
			ft_putchar((n % base) + 48);
		else
			ft_putchar((n % base) - 10 + 65);
	}
}

void print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int i;
	char *stringtable;
	struct nlist_64 *element;
	struct nlist_64 *testu;
	const char *type;

	i = 0;
	int j = 0;
	element = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	while (i < nsyms)
	{
		type = NULL;
		switch(element[i].n_type & N_TYPE) {
			case N_UNDF: type = "U"; break;
			case N_INDR:  type = "I"; break;
			case N_ABS: type = "A"; break;
			case N_SECT: type = "S"; break;
			case N_PBUD: type = "P"; break;
			default:
				// fprintf(stderr, "Invalid symbol type: 0x%x ", element[i].n_type);
				j = -1;
				// return ;
			}
			char test[10];
			if (j == 0 && ft_strlen(stringtable + element[i].n_un.n_strx) > 0) {
				// printf("|| %x element type N_TYPE for %s||", element[i].n_type, stringtable + element[i].n_un.n_strx);
				// printf("%d\n", element[i].n_type & N_TYPE);
				// printf("%d\n", element[i].n_type & N_EXT);
				printf("%d", element[i].n_sect);
				// ft_putstr(type);
				// ft_putchar(' ');
				// ft_putnbr_base(element[i].n_value, 16);
				// ft_putchar(' ');
				// if (ft_strlen(stringtable + element[i].n_un.n_strx) == 0) ft_putstr("element + tringtable is NULL");
				// else ft_putstr(stringtable + element[i].n_un.n_strx);
				// ft_putchar('\n');
			}
		j = 0;
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
	// printf("%u -> MAGIC\n%u -> FILETYPE\n%u -> FLAGS\n", header->magic, header->filetype, header->flags);
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
		// puts("Binaire pour 32-bits");
	}
	if (magic_number == MH_MAGIC_64)
	{
		// puts("Binaire pour 64-bits");
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