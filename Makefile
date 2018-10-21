# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2018/10/21 15:19:36 by zadrien          ###   ########.fr        #
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
SFILES= server/main.c server/pi/serverPI.c server/pi/auth.c server/pi/auth_utils.c server/pi/ft_list.c \
		dtp/recept.c dtp/send.c dtp/dtp-utils.c dtp/dtp-server.c dtp/stream-handler.c \
		server/dtp/get-server.c server/dtp/put-server.c \

CFILES= user/main.c user/pi/com_link.c user/pi/userPI.c user/pi/lls.c user/pi/lpwd.c user/pi/lcd.c \
		dtp/recept.c dtp/send.c dtp/dtp-utils.c dtp/dtp-client.c dtp/stream-handler.c \
		user/pi/pi-utils.c user/dtp/get-client.c user/dtp/put-client.c \

OSFILES= $(SFILES:.c=.o)
OCFILES= $(CFILES:.c=.o)

HFILES= includes/server.h \
		includes/user.h \
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
	@mkdir -p $(OPATH)user/
	@mkdir -p $(OPATH)user/dtp
	@mkdir -p $(OPATH)user/pi
	@mkdir -p $(OPATH)server/
	@mkdir -p $(OPATH)server/dtp
	@mkdir -p $(OPATH)server/pi
	@mkdir -p $(OPATH)dtp

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
