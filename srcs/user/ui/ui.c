/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:37:50 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/28 11:22:41 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

int     return_line(t_line *line)
{
    write(1, "\n", 1);
    (void)line;
    return (1);
}

int     cursor_motion(t_line *line)
{
    int         i;
    static const t_input    in[2] = {{AR_RIGHT, &cm_right}, {AR_LEFT, &cm_left}};

    i = -1;
    while (++i < 2)
    {
        if (line->buf[2] == in[i].key)
            return (in[i].f(line));
    }
    return (0);
}
int     ft_tab(t_line *line)
{
    (void)line;

    return (0);
}
int    keyboard(t_line *line)
{
    int                     i;
    static const t_input    ref[3] = {{ENTER, &return_line}, {DEL, &del_char}, {TAB, &ft_tab}};

    i = -1;
    // printf("%d | %d | %d | %d\n", line->buf[0], line->buf[1], line->buf[2], line->buf[3]);
    while (++i < 3)
    {
        if (line->buf[0] == ref[i].key)
            return (ref[i].f(line));
    }
    if (line->buf[0] >= 32 && line->buf[0] <= 126)
        print_char(line);
    else
        return (cursor_motion(line));
    return (0);
}

int     restore_value(t_line *line)
{
    line->x = 0;
    line->cur = 0;
    line->y = 0;
    line->len = 0;
    line->str_len = 50;
    ft_strdel(&line->str);
    if (!(line->str = (char*)malloc(sizeof(char) * line->str_len)))
        return (0);
    
    ft_bzero(line->str, line->str_len);
    return (1);
}

t_line  *get_line(char *prompt, int printable)
{
    t_line  *line;

    line = init_line(ft_strlen(prompt), printable);
    ft_putstr_fd(prompt, 2);
    while (1)
    {
        if (read(0, line->buf, 6) == 0)
            break ;
        if (keyboard(line))
            return (line);
    }
    free_line(line);
    return (NULL);
}

void    start_line(t_edit *term, int socket, int printable, char *prompt)
{
    int     r;
    t_line  *line;

    line = init_line(ft_strlen(prompt), printable);
    ft_putstr_fd(prompt, 2);
    while (1)
    {
        ft_memset(line->buf, '\0', 6);
        if (read(0, line->buf, 6) == 0)
            break ;
        if (keyboard(line))
        {
            if ((r = userPI(line->str, socket)) == -1)
                break ;
            else if (r == 1)
                ft_putendl_fd("success", 2);
            else
                ft_putendl_fd("error", 2);
            mode_on(term);
            restore_value(line);
            ft_putstr_fd(prompt, 2);
        }
    }
    free_line(line);
}