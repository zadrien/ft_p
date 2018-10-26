/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:38:59 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/26 12:04:44 by zadrien          ###   ########.fr       */
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

# define CM_GRP 27
# define CTRL_D 4
# define ENTER 10
# define TAB 9
# define DEL 127

/**
 * SECOND CHECKING CM_GRP
 */
# define INSERT 50
# define DEL_FW 51
# define PGUP 53
# define PGDN 54
# define AR_RIGHT 67
# define AR_LEFT 68
# define AR_UP 65
# define AR_DW 66
# define HOME 72
# define END 70

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

typedef struct		s_line
{
	char			*str;
	char			buf[6];
	size_t			x;
	size_t			y;
	size_t			max;
	size_t			offset;
	size_t			cur;
	size_t			str_len;
	size_t			len;

}					t_line;

typedef struct		s_edit
{
	t_ch			*select;
	char			*name_term;
	struct termios	term;
}					t_edit;

typedef struct      s_input
{
    int     key;
    int     (*f)(t_line *line);
}                   t_input;


int     init_term(t_edit **edit, int i);
t_edit	*init_cmd_line(void);
t_line  *init_line(int offset);
void    change_value(t_edit **edit, int i);
int     window_size(void);
int     usefull(int i);


/**
 * Arrow input
*/
int     cm_left(t_line *line);
int     cm_right(t_line *line);
int     print_char(t_line *line);
int     replace_cursor(t_line *line, int mode);
int     insert_char(t_line *line);
int     print_char(t_line *line);
int    realloc_line(t_line *line);
int     old_pos(t_line *line, size_t len);


#endif