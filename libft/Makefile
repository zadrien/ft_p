# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 20:05:29 by zadrien           #+#    #+#              #
#    Updated: 2017/07/31 14:48:00 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c	\
		\
		ft_memalloc.c ft_memccpy.c ft_memmove.c ft_memcpy.c ft_memcmp.c	\
		ft_memchr.c ft_memdel.c ft_memset.c ft_strdup.c	\
		\
		ft_putchar_fd.c ft_putchar.c ft_putendl.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_putnbr.c ft_putstr_fd.c ft_putstr.c	\
		\
		ft_strjoin.c ft_strlcat.c ft_strncat.c ft_strcat.c ft_strncmp.c	\
		ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c	\
		ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_strjoinf.c	\
		\
		ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strequ.c	\
		ft_striter.c ft_striteri.c ft_strlen.c ft_strmap.c ft_strmapi.c	\
		ft_strstr.c ft_itoa.c ft_putstr.c ft_strdel.c ft_strcpy.c	\
		\
		ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c	\
		ft_lstmap.c ft_putnbroct.c get_next_line.c ft_errormsg.c ft_split.c	\
		ft_putendn.c count_tab.c find_node.c	\

OBJS = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
		@gcc $(FLAG) -c $(SRC)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)

clean:
		@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
