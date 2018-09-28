# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2018/09/28 11:46:40 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean name re

CC= gcc
SNAME= server
CNAME= client
CFLAGS= -g -Wall -Werror -Wextra
CPATH= srcs/
OPATH= obj/
HPATH= includes/ libft/
INC= $(addprefix -I , $(HPATH))
SFILES= main.c execution.c features/login/login.c\

CFILES= client/client.c \

OSFILES= $(SFILES:.c=.o)
OCFILES= $(CFILES:.c=.o)

HFILES= includes/ftp.h \
		libft/libft.h	\

SOBJ= $(addprefix $(OPATH), $(OSFILES))
COBJ= $(addprefix $(OPATH), $(OCFILES))

all: $(SNAME) $(CNAME)

$(SNAME): $(SOBJ)
	make -C libft
	$(CC) $(CFLAGS) $(SOBJ) -ltermcap libft/libft.a -o $(SNAME)

$(CNAME): $(COBJ)
	$(CC) $(CFLAGS) $(COBJ) -ltermcap libft/libft.a -o $(CNAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)client
	@mkdir -p $(OPATH)features
	@mkdir -p $(OPATH)features/login

	$(CC) -g -Wall -Werror -Wextra  $(INC) $< -c -o $@

clean:
	make -C libft clean
	rm -rf $(SOBJ) $(COBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(SNAME) $(CNAME)
	rm -rf $(OPATH)

re: fclean all

norme:
		@norminette srcs/**/**.[ch]
		@norminette libft/*.[ch]
