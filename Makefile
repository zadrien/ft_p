# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2017/07/31 15:07:34 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean name re

CC= gcc
NAME= ftp
CFLAGS= -g -Wall -Werror -Wextra
CPATH= srcs/
OPATH= obj/
HPATH= includes/ libft/
INC= $(addprefix -I , $(HPATH))
CFILES= main.c \

OFILES= $(CFILES:.c=.o)

HFILES= includes/ftp.h \
		libft/libft.h	\

OBJ= $(addprefix $(OPATH), $(OFILES))

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -ltermcap libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)/edit_line

	$(CC) -g -Wall -Werror -Wextra  $(INC) $< -c -o $@

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)
	rm -rf $(OPATH)

re: fclean all

norme:
		@norminette srcs/**/**.[ch]
		@norminette libft/*.[ch]
