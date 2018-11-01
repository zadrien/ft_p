/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 18:28:08 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 10:26:52 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    realloc_line(t_line *line)
{
    int     i;
    char    *tmp;

    i = -1;
    tmp = ft_strdup(line->str);
    ft_strdel(&line->str);
    line->str_len += 50;
    if (!(line->str = (char*)malloc(sizeof(char) * line->str_len)))
        return (0);
    ft_bzero(line->str, line->str_len);
    while (tmp[++i])
        line->str[i] = tmp[i];
    ft_strdel(&tmp);
    return (1);
}

int     multi_pos(t_line *line, size_t len)
{
    size_t  i;

    i = line->cur;
    if (line->print)
        while (len)
        {
            line->cur++;
            line->x++;
            if (line->y == 0 && line->x == (line->winsize - line->offset))
            {
                line->y++;
                line->x = 0;
            } else if (line->y > 0 && line->x == line->winsize) {
                line->y++;
                line->x = 0;
            }
            len--;
        }
    while (line->cur > i)
        cm_left(line);
    return (1);
}

int     old_pos(t_line *line, size_t len)
{
    if (line->print && line->y == 0 && line->x == (line->winsize - line->offset))
    {
        line->x = 0;
        line->y++;
        tputs(tgoto(tgetstr("cr", NULL), line->x, line->y), 1, usefull);
    } else if (line->print && line->y > 0 && line->x == line->winsize) {
        line->y++;
        line->x = 0;
        tputs(tgoto(tgetstr("cr", NULL), line->x, line->y), 1, usefull);
    } else
        multi_pos(line, len);
    return (1);
}

int     replace_cursor(t_line *line, int mode)
{
    size_t     i;

    i = 0;
    if (mode == AR_LEFT)
    {
        i = line->x;
        while (i-- > line->cur)
            tputs(tgoto(tgetstr("le", NULL), line->x, line->y), 1, usefull);
    } else if (mode == END) {
        while (++i < line->winsize)
            tputs(tgoto(tgetstr("nd", NULL), line->x, line->y), 1, usefull);
    }
    return (1);
}