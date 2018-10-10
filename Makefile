# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2018/10/10 11:37:57 by zadrien          ###   ########.fr        #
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

CFILES= user/main.c user/pi/com_link.c user/pi/userPI.c \

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
	@mkdir -p $(OPATH)user/pi
	@mkdir -p $(OPATH)server/
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
