/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:38:42 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/27 16:10:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"


void    free_line(t_line *line)
{
    if (line)
    {
        if (line->str)
            ft_strdel(&line->str);
        free(line);
    }
}

t_line  *init_line(size_t offset, int printable)
{
    t_line *tmp;
    if (!(tmp = (t_line*)malloc(sizeof(t_line))))
        return (NULL);
    if (!(tmp->str = (char*)malloc(sizeof(char) * 50)))
        return (NULL);
    ft_bzero(tmp->str, 50);
    tmp->str_len = 50;
    tmp->len = 0;
    tmp->x = 0;
    tmp->y = 0;
    tmp->cur = 0;
    tmp->winsize = window_size();
    tmp->offset = offset;
    tmp->print = printable;
    return (tmp);
}

int    change_value(t_edit **edit, int i)
{
    t_edit  *tmp;

    tmp = *edit;
    if (i)
    {
        tmp->term.c_lflag &= ~(ICANON | ECHO);
        tmp->term.c_cc[VMIN] = 1;
        tmp->term.c_cc[VTIME] = 0;
    
    } else if (i == 0)
    {
        tmp->term.c_lflag |= ~(ICANON | ECHO);
        tmp->term.c_cc[VMIN] = 1;
        tmp->term.c_cc[VTIME] = 0;
    }
    if (tcsetattr(1, TCSADRAIN, &tmp->term) == -1)
    {
        ft_putendl_fd("set-shell: tcsetattr: ERROR", 2);
        return (0);
    }
    return (1);
}

int     mode_off(t_edit *term)
{
    term->term.c_lflag |= ~(ICANON | ECHO);
    if (tcsetattr(1, TCSADRAIN, &term->term) == -1)
    {
        ft_putendl_fd("set-shell: tcsetattr: ERROR", 2);
        return (0);
    }
    return (1);
}

int     mode_on(t_edit *term)
{
    term->term.c_lflag &= ~(ICANON | ECHO);
    term->term.c_cc[VMIN] = 1;
    term->term.c_cc[VTIME] = 0;
    while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
        kill(-g_shell_pgid, SIGTTIN);
    tcsetpgrp(g_shell_terminal, g_shell_pgid);
    if (tcsetattr(1, TCSADRAIN, &term->term) == -1)
    {
        ft_putendl_fd("set-shell: tcsetattr: ERROR", 2);
        return (0);
    }
    return (1);
}

int     init_term(t_edit *edit)
{
    g_shell_terminal = STDIN_FILENO;
    if ((g_shell_is_interactive = isatty(g_shell_terminal)))
    {
        while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
            kill(-g_shell_pgid, SIGTTIN);
        if (tgetent(0, edit->name_term) == ERR)
        {
            ft_putendl_fd("set-shell: tgetent: ERROR", 2);
            return (0);
        }
        if (tcgetattr(1, &edit->term) == -1)
        {
            ft_putendl_fd("set-shell: tcgetattr: ERROR", 2);
            return (0);
        }
        if (mode_on(edit))
            return (1);
    }
    // if (tmp)
    // {
    //     if (tgetent(NULL, tmp->name_term) == -1)
    //         return (-1);
    //     if (tcgetattr(0, &(tmp)->term) == -1)
    //         return (-1);
    //     if (change_value(&tmp, i))
    //         return (1);
    //     // if (tcsetattr(0, TCSANOW, &(tmp)->term) == -1)
    //     //     return (-1);
    //     // return (1);
    // }
    return (0);
}

t_edit     *init_cmd_line(void)
{
    t_edit  *tmp;

    if (!(tmp = (t_edit*)malloc(sizeof(t_edit))))
        return (NULL);
    if ((tmp->name_term = getenv("TERM")) == NULL)
        return (NULL);
    return (tmp);
}