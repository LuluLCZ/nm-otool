/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrupt64_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:10:50 by llacaze           #+#    #+#             */
/*   Updated: 2020/01/14 14:10:58 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int		error_64_1(uint32_t index, uint64_t size, int i, t_file file)
{
	if (i == 0 && size > file.size)
	{
		ft_putstr_fd("/Applications/Xcode.app/Contents/Developer/Toolchains\
		/XcodeDefault.xctoolchain/usr/bin/nm: ", 2);
		ft_putstr_fd(file.filename, 2);
		ft_putstr_fd(" truncated or malformed object (offset field plus \
		size field of section ", 2);
		ft_putnbr_fd(index, 2);
		ft_putendl_fd(" in LC_SEGMENT_64 command 1 extends past the end \
		of the file)\n", 2);
		return (-1);
	}
	return (0);
}
