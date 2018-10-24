/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:38:59 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/24 19:05:52 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LINE_H
# define CMD_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"

enum on_off
{
    OFF = 0,
    ON = 1
};
 
typedef struct		s_choise
{
	char			*str;
	int				i;
	int				sel;
	struct s_choise	*prev;
	struct s_choise	*next;
}					t_ch;

typedef struct		s_edit
{
    char            *line;
    int             x;
    int             y;
	t_ch			*select;
	char			*name_term;
	struct termios	term;
}					t_edit;


#endif