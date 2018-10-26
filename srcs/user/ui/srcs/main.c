/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:37:50 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/26 12:57:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"




void    cursor_display(int mod)
{
    tputs(tgetstr((mod ? "ve" : "vi"), NULL), 1, usefull);
}


int     return_line(t_line *line)
{
    write(1, "\n", 1);
    (void)line;
    return (1);
}
int     spec_char(t_line *line)
{
    // (void)line;
    // int                     i;
    int                     c;
    // int                     m = 3;
    // static const t_input    in[3] = {{AR_RIGHT, &cm_right}, {AR_LEFT, &cm_left}, {ENTER, &return_line}};

    // i = -1;
    c = *(int*)line->buf;
    printf("%d\n", c);
    printf("%d | %d | %d | %d\n", line->buf[0], line->buf[1], line->buf[2], line->buf[3]);
    if (line->buf[0] == 10)
        return (1);
    // while (++i < m)
    // {
    //     if (c == in[i].key)
    //         return (in[i].f(line));
    // }
    return (0);
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

int    keyboard(t_line *line)
{
    int                     i;
    static const t_input    ref[2] = {{ENTER, &return_line}, {DEL, &del_char}};

    i = -1;
    while (++i < 2)
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

void    start_line(int display)
{
    t_line  *line;

    line = init_line(3);
    display == OFF ? cursor_display(OFF) : 0;
    ft_putstr_fd("$> ", 2);
    while (1)
    {
        read(0, line->buf, 6);
        if (keyboard(line))
        {
            printf("line=%s\n", line->str);
            printf("cursor position=%zd character=[%c]\n", line->cur, line->str[line->cur]);
            printf("line->cur = %zd | line->x = %zd | line->y = %zd\n", line->cur, line->x, line->y);
            line->x = 0;
            line->cur = 0;
            line->y = 0;
            line->len = 0;
            ft_bzero(line->str, line->str_len);
            ft_putstr_fd("$> ", 2);
        }
        // motion(line, key, offset);
    }
}

int     main(int ac, char **av)
{
    // int     key;
    t_edit  *edit;

    if (ac == 1 && av)
    {
        if (!(edit = init_cmd_line()))
            return (0);
        if (init_term(&edit, 1))
            start_line(ON);
    }
}