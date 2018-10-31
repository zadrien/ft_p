# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2018/10/31 16:35:39 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean name re

CC= gcc
SNAME= server
CNAME= client
CFLAGS= -g -Wall -Werror -Wextra
CPATH= srcs/
OPATH= obj/
HPATH= includes/ libft/includes/
INC= $(addprefix -I , $(HPATH))
SFILES= server/main.c \
		server/pi/serverPI.c server/pi/auth.c server/pi/auth_utils.c server/pi/auth_creat.c \
		server/pi/ft_list.c server/pi/cwd.c server/pi/utils_list.c \
		server/dtp/get-server.c server/dtp/put-server.c \
		server/dtp/dtp-server.c server/dtp/dtp-utils.c server/dtp/dtp-misc.c \

CFILES= user/main.c \
		user/pi/com_link.c user/pi/userPI.c user/pi/lls.c user/pi/lpwd.c \
		user/pi/lcd.c /user/pi/auth.c user/pi/ft_cwd.c user/pi/pi-utils.c \
		user/dtp/get-client.c user/dtp/put-client.c \
		user/dtp/dtp-client.c user/dtp/dtp-utils.c user/dtp/dtp-misc.c \

OSFILES= $(SFILES:.c=.o)
OCFILES= $(CFILES:.c=.o)

HFILES= libft/includes/libft.h	\
		includes/ftp.h \

SOBJ= $(addprefix $(OPATH), $(OSFILES))
COBJ= $(addprefix $(OPATH), $(OCFILES))

all: $(SNAME) $(CNAME)

$(SNAME): $(SOBJ)
	make -C libft
	$(CC) $(CFLAGS) -ltermcap $(SOBJ) libft/libft.a -o $(SNAME)

$(CNAME): $(COBJ)
	$(CC) $(CFLAGS) -ltermcap $(COBJ) libft/libft.a -o $(CNAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)user/
	@mkdir -p $(OPATH)user/dtp
	@mkdir -p $(OPATH)user/pi
	@mkdir -p $(OPATH)server/
	@mkdir -p $(OPATH)server/dtp
	@mkdir -p $(OPATH)server/pi

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

