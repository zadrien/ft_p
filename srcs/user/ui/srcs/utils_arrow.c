/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 11:55:08 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/26 12:05:37 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

int     print_char(t_line *line)
{
    if (ft_strlen(line->str) == (line->str_len - 1))
        if (!realloc_line(line))
            ft_putendl("FAIL");
    if (line->cur == line->len)
    {
        line->str[line->len] = line->buf[0];
        line->x++;
        line->cur++;
        write(1, &line->buf[0], 1);
        if (line->y == 0 && line->x == (line->max - line->offset))
        {
            tputs(tgoto(tgetstr("do", NULL), line->x, line->y), 1, usefull);
            tputs(tgoto(tgetstr("cr", NULL), line->x, line->y), 1, usefull);
            line->x = 0;
            line->y++;
        } else if (line->y > 0 && line->x == line->max) {
            line->y++;
            line->x = 0;
            tputs(tgoto(tgetstr("do", NULL), line->x, line->y), 1, usefull);
            tputs(tgoto(tgetstr("cr", NULL), line->x, line->y), 1, usefull);
        }
    } else if (line->cur < line->len) {
        insert_char(line);
    }
    line->len++;
    return (0);
}

int     insert_char(t_line *line)
{
    int     i;
    int     j;
    char    *tmp;

    j = 0;
    i = line->cur + 1;
    tmp = ft_strdup(line->str + line->cur);
    write(1, &line->buf[0], 1);
    write(1, tmp, ft_strlen(tmp));
    line->str[line->cur] = line->buf[0];
    while (tmp[j])
    {
        line->str[i++] = tmp[j];
        j++;
    }
    line->x++;
    line->cur++;
    old_pos(line, ft_strlen(tmp));
    ft_strdel(&tmp);
    return (1);
}