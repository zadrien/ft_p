# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 20:05:29 by zadrien           #+#    #+#              #
#    Updated: 2018/11/01 08:33:30 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAG = -Wall -Wextra -Werror -ltermcap
CPATH= srcs/
OPATH= obj/
HPATH= includes/
INC= $(addprefix -I , $(HPATH))
HFILES= includes/libft.h \

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
		parser.c free_token.c new_env.c add_env.c\
		ft_countarg.c ft_strndup.c ft_freetab.c print_msg.c \
		cmd_line/init.c cmd_line/misc_init.c cmd_line/arrow.c cmd_line/utils_arrow.c cmd_line/misc_arrow.c \
		cmd_line/ui.c \

OBJS = $(SRC:.c=.o)

LOBJ= $(addprefix $(OPATH), $(OBJS))


all: $(NAME)


$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	@mkdir -p $(OPATH)cmd_line/

	gcc -c -o $@ $< $(FLAG) $(INC)

$(NAME): $(LOBJ)
	ar rc $(NAME) $(LOBJ)
	ranlib $(NAME)
clean:
		@rm -rf $(LOBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OPATH)
re: fclean all