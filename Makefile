# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/20 21:33:19 by llacaze           #+#    #+#              #
#    Updated: 2019/11/20 22:38:24 by llacaze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

INC_PATH = includes
LIB_PATH = libft
BUILD_PATH = objets

SRCS =	main.c \
			init_list.c

LIB_SRCS = $(LIB_PATH)/libft.a

OBJECTS = $(SOURCES:%.c=$(BUILD_PATH)/%.o)

CC = gcc

OPTIONS = -c

CFLAGS = -g3 -Wall -Wextra -Werror

RM = rm -Rfv

SRC =	main.c \
		init_list.c


OBJ = $(SRC:.c=.o)

DIR_SRC = nm/sources
DIR_OBJ = nm/objs

SRCS = $(addprefix $(DIR_SRC)/,$(SRC))
OBJS = $(addprefix $(DIR_OBJ)/,$(OBJ))

HEAD_DIR = ./libft/

all:  $(NAME)

$(NAME) : libft $(OBJS)
		$(RM) $(NAME)
		$(CC) -o $@ $(OBJS) $(HEAD_DIR)/libft.a

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
		@mkdir -p $(DIR_OBJ)
		$(CC) -c -o $@ -I./includes/ -I./libft/includes $^

libft:
		make -C $(HEAD_DIR)

clean:
		$(RM) $(OBJS)
		cd $(HEAD_DIR) && $(MAKE) $@

fclean: clean
		$(RM) $(NAME)


		make -C $(HEAD_DIR) fclean

re: fclean all

.PHONY : all clean fclean re libft