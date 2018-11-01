/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 15:32:31 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 08:33:20 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# define BUFF_SIZE 10

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env   			*new_env(char **env);
int     			add_env(t_env **env, char **var);
t_env				*find_node(t_env **env, char *var, char *value);


typedef struct		s_token
{
	char			*str;
	int				*type;
	struct s_token	*next;
}					t_token;

typedef	struct		s_key
{
	int				key;
	void			(*f)(t_token** ,char**, char*, int*);
}					t_key;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap (t_list *lst, t_list *(*f)(t_list *elem));
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little,
									size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbroct(int n);
int					get_next_line(int fd, char **line);
int					ft_errormsg(char *env, char *cmd, char *str);
char				**ft_split(char const *s);
void				ft_putendn(int i);
int					count_tab(char **ta);
char				*ft_strjoinf(char *s1, char *s2, int w);
t_token				*parser(char *aastr);
void				init_token(t_token **tok);
void				free_token(t_token **token);
int					ft_countarg(t_token **lst);
char			    *ft_strndup(char *str, size_t len);
void    ft_freetab(char **trash);

/**
 * COMMAND LINE
 */

/**
 * COLORS
 */
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

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

size_t				g_win;
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

void    free_line(t_line *line);
t_line  *init_line(size_t offset, int printable);
int    	change_value(t_edit **edit, int i);
int     mode_off(t_edit *term);
int     mode_on(t_edit *term);
int     shell_sig(void);
int     init_term(t_edit *edit);
t_edit  *init_cmd_line(void);
int     usefull(int i);
int     window_size(void);
int    realloc_line(t_line *line);
int     multi_pos(t_line *line, size_t len);
int     old_pos(t_line *line, size_t len);
int     replace_cursor(t_line *line, int mode);
int     cm_left(t_line *line);
int     cm_right(t_line *line);
int     del_char(t_line *line);
void    next_line(t_line *line);
int     print_char(t_line *line);
int     insert_char(t_line *line);
int     return_line(t_line *line);
int     cursor_motion(t_line *line);
int     ft_tab(t_line *line);
int		keyboard(t_line *line);
int     restore_value(t_line *line);
t_line  *get_line(char *prompt, int printable);
void    print_msg(char *str, char *color, int fd);

#endif
