# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2018/10/25 18:30:13 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean name re

CC= gcc
NAME= cmd_line
FLAGS= -g -Wall -Werror -Wextra
SPATH= srcs/
OPATH= obj/
HPATH= includes/ libft/
INC= $(addprefix -I , $(HPATH))
SFILES= main.c \
		arrow.c init.c misc_init.c misc_arrow.c \

OSFILES= $(SFILES:.c=.o)

HFILES= includes/cmd_line.h \

SOBJ= $(addprefix $(OPATH), $(OSFILES))

all: $(NAME) $(CNAME)

$(NAME): $(SOBJ)
	make -C libft
	$(CC) $(FLAGS) -ltermcap $(SOBJ)  libft/libft.a -o $(NAME)

$(OPATH)%.o: $(SPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)

	$(CC) -g -Wall -Werror -Wextra  $(INC) $< -c -o $@

clean:
	make -C libft clean
	rm -rf $(SOBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)
	rm -rf $(OPATH)

re: fclean all

norme:
		@norminette srcs/**/**.[ch]
		@norminette libft/*.[ch]