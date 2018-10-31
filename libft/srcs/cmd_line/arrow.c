/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:49 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 10:26:34 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     cm_left(t_line *line)
{
    if (line->cur > 0)
    {
        line->cur--;
        if (line->print && line->y == 0)
        {
            line->x--;
            tputs(tgoto(tgetstr("le", NULL), line->x, line->y), 1, usefull);
        } else if (line->print && line->y > 0) {
            if (line->x == 0)
            {
                line->y--;
                line->x = (line->y == 0 ? (line->winsize - line->offset) : line->winsize);
                line->x--;
                tputs(tgoto(tgetstr("up", NULL), line->x, line->y), 1, usefull);
                replace_cursor(line, END);           
            } else {
                line->x--;
                tputs(tgoto(tgetstr("le", NULL), line->x, line->y), 1, usefull);            
            }
        }
    }
    return (0);
}

int     cm_right(t_line *line)
{
    if (line->cur < line->len)
    {
        line->cur++;
        if (line->print && line->y == 0)
        {
            if (line->x < (line->winsize - line->offset))
            {
                line->x++;
                tputs(tgoto(tgetstr("nd", NULL), line->x, line->y), 1, usefull);
            }
            if (line->x == (line->winsize - line->offset))
                next_line(line);
        } else if (line->print && line->y > 0) {
            line->x++;
            if (line->x == line->winsize)
                next_line(line);
            else if (line->x < line->winsize)
                tputs(tgoto(tgetstr("nd", NULL), line->x, line->y), 1, usefull);
        }
    }
    return (0);
}

int     del_char(t_line *line)
{
    size_t  i;
    size_t  j;
    char    *tmp;

    j = -1;
    if (line->cur <= line->len && line->cur > 0)
    {
        tmp = ft_strdup(line->str + line->cur);
        i = line->cur - 1;
        while (tmp[++j])
            line->str[i++] = tmp[j];
        line->str[i] = '\0';
        if (line->print)
        {
            cm_left(line);
            tputs(tgoto(tgetstr("sc", NULL), line->x, line->y), 1, usefull);
            write(1, tmp, ft_strlen(tmp));
            write(1, " ", 1);
            tputs(tgoto(tgetstr("rc", NULL), line->x, line->y), 1, usefull);
            ft_strdel(&tmp);
        }
        line->len--;
    }
    return (0);
}