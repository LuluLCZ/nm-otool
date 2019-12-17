# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/20 21:33:19 by llacaze           #+#    #+#              #
#    Updated: 2019/12/17 18:03:12 by llacaze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm_otool
NAME1 = ft_nm
NAME2 = ft_otool

CC = gcc

OPTIONS = -c

CFLAGS = -g3 -Wall -Wextra -Werror

RM = rm -Rfv

SRC =	main.c \
		init_list.c\
		ft_swap_list.c\
		macho64.c\
		macho32.c\
		fat32.c\
		corrupt64.c\
		macho64_tools.c\
		corrupt32.c\
		macho32_tools.c\

SRC1 = $(SRC)
SRC2 = $(SRC)

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

DIR_SRC = sources
DIR_OBJ = objs

SRCS1 = ft_nm.c $(addprefix $(DIR_SRC)/,$(SRC1))
SRCS2 = ft_otool.c $(addprefix $(DIR_SRC)/,$(SRC2))
OBJS1 = ft_nm.o $(addprefix $(DIR_OBJ)/,$(OBJ1))
OBJS2 = ft_otool.o $(addprefix $(DIR_OBJ)/,$(OBJ2))

HEAD_DIR = ./libft/

all:  $(NAME)

$(NAME): $(NAME1) $(NAME2)

$(NAME1) : libft $(OBJS1)
		$(RM) $(NAME1)
		$(CC) $(CFLAGS) -o $@ $(OBJS1) $(HEAD_DIR)/libft.a

$(NAME2) : libft $(OBJS2)
		$(RM) $(NAME2)
		$(CC) $(CFLAGS) -o $@ $(OBJS2) $(HEAD_DIR)/libft.a

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
		@mkdir -p $(DIR_OBJ)
		$(CC) $(CFLAGS) -c -o $@ -I./includes/ -I./libft/includes $^

libft:
		make -C $(HEAD_DIR)

clean:
		$(RM) $(OBJS1) $(OBJS2)
		cd $(HEAD_DIR) && $(MAKE) $@

fclean: clean
		$(RM) $(NAME1) $(NAME2)


		make -C $(HEAD_DIR) fclean

re: fclean all

.PHONY : all clean fclean re libft