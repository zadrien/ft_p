# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2018/09/30 16:13:48 by zadrien          ###   ########.fr        #
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
SFILES= main.c execution/server/execution.c features/login/login.c\

CFILES= client.c execution/client/client_exec.c execution/client/lcd.c \
		execution/client/lls.c execution/client/lpwd.c execution/get.c \

OSFILES= $(SFILES:.c=.o)
OCFILES= $(CFILES:.c=.o)

HFILES= includes/ftp.h \
		libft/libft.h	\

SOBJ= $(addprefix $(OPATH), $(OSFILES))
COBJ= $(addprefix $(OPATH), $(OCFILES))

all: $(SNAME) $(CNAME)

$(SNAME): $(SOBJ)
	make -C libft
	$(CC) $(CFLAGS) $(SOBJ) libft/libft.a -o $(SNAME)

$(CNAME): $(COBJ)
	$(CC) $(CFLAGS) $(COBJ) libft/libft.a -o $(CNAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)features
	@mkdir -p $(OPATH)features/login
	@mkdir -p $(OPATH)execution/
	@mkdir -p $(OPATH)execution/client
	@mkdir -p $(OPATH)execution/server


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
