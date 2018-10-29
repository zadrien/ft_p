/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:17:40 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 09:04:02 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_H
# define USER_H

# include <netdb.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <stdlib.h>


# include "libft.h"
# include "dtp.h"

/**
 * USER INTERFACE
*/
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

int                 g_shell_terminal;
int                 g_shell_is_interactive;
pid_t               g_shell_pgid;
struct termios		g_shell_termios;
typedef void		sigfunc(int);
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

typedef struct		s_window
{
	size_t			x;
	size_t			y;
	size_t			winsize;
}					t_window;

t_window			g_win;

typedef struct		s_line
{
	char			*str;
	char			buf[6];
	int				print;
	size_t			x;
	size_t			y;
	size_t			cur;
	size_t			len;
	size_t			winsize;
	size_t			offset;
	size_t			str_len;

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

t_edit  *init_cmd_line(void);
int     init_term(t_edit *edit);
int     change_value(t_edit **edit, int i);
t_line  *init_line(size_t offset, int printable);
int     usefull(int i);
int     window_size(void);
int     mode_on(t_edit *term);
int     mode_off(t_edit *term);


void    start_line(t_edit *term, int socket, int printable, char *prompt);
int     restore_value(t_line *line);
int     keyboard(t_line *line);
t_line  *get_line(char *prompt, int printable);
void    free_line(t_line *line);

int     ft_tab(t_line *line);
int     cursor_motion(t_line *line);
int     return_line(t_line *line);
int     cm_left(t_line *line);
int     cm_right(t_line *line);
int     del_char(t_line *line);

int     realloc_line(t_line *line);
int     multi_pos(t_line *line, size_t len);
int     old_pos(t_line *line, size_t len);
int     replace_cursor(t_line *line, int mode);

void    next_line(t_line *line);
int     print_char(t_line *line);
int     insert_char(t_line *line);

char    *ft_struct(char *cmd, t_token **arg);
int     userPI(char *str, int s);
int     com_link(char *addr, char *port);
int     ft_lls(t_token **lst, int socket);
int     c_get(t_token **lst, int s);
int     c_put(t_token **lst, int s);
int     wait_response(int s, int res);
/**
 * Authentification
*/
int     auth(t_token **lst, int s);
int     create_user(int s, char *name);
int     create_password(int s, char *pass);
int     create_pass(t_token **lst, int s);


/**
 * Directory
*/
int     ft_lpwd(t_token **lst, int socket);
int    ft_pwd(t_token **lst, int s);
int     ft_lcd(t_token **lst, int socket);
int     ft_cwd(t_token **lst, int s);
#endif