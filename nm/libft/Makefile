# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/09 16:14:07 by llacaze           #+#    #+#              #
#    Updated: 2019/10/10 16:26:32 by llacaze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -Rf

SRCDIR =	srcs
OBJDIR =	objs
INCDIR =	includes

SRC =   ft_atoi.c			\
		ft_remove_char.c	\
		ft_free_tab.c		\
		ft_count_char.c		\
		ft_check_double.c	\
		ft_bzero.c			\
		ft_isalnum.c		\
		ft_isalpha.c		\
		ft_isascii.c		\
		ft_isdigit.c		\
		ft_isprint.c		\
		ft_itoa.c			\
		ft_memalloc.c		\
		ft_memccpy.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_memcpy.c			\
		ft_memdel.c			\
		ft_memmove.c		\
		ft_memset.c			\
		ft_putchar_fd.c		\
		ft_putchar.c		\
		ft_putendl_fd.c		\
		ft_putendl.c		\
		ft_putnbr_fd.c		\
		ft_putnbr.c			\
		ft_putstr_fd.c		\
		ft_putstr.c			\
		ft_strcat.c			\
		ft_strchr.c			\
		ft_strclr.c			\
		ft_strcmp.c			\
		ft_strcpy.c			\
		ft_strdel.c			\
		ft_strdup.c			\
		ft_strequ.c			\
		ft_striter.c		\
		ft_striteri.c		\
		ft_strjoin.c		\
		ft_strlcat.c		\
		ft_strlen.c			\
		ft_strmap.c			\
		ft_strmapi.c		\
		ft_strncat.c		\
		ft_strncat.c		\
		ft_strncmp.c		\
		ft_strncpy.c		\
		ft_strnequ.c		\
		ft_strnew.c			\
		ft_strnstr.c		\
		ft_strrchr.c		\
		ft_strsplit.c		\
		ft_strstr.c			\
		ft_strsub.c			\
		ft_strtrim.c		\
		ft_tolower.c		\
		ft_toupper.c		\
		ft_lstnew.c			\
		ft_lstdelone.c		\
		ft_lstdel.c			\
		ft_lstadd.c			\
		ft_lstiter.c		\
		ft_lstmap.c

OBJP =	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCP =	$(foreach dir, $(INCDIR), -I$(dir))

all: $(OBJDIR) $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $^ $(INCS_DIRS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJP) Makefile
	@ar rcs $(NAME) $(OBJP)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(OBJDIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re