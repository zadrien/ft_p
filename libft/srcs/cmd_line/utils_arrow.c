/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 11:55:08 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 10:26:28 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    next_line(t_line *line)
{
    line->y++;
    line->x = 0;
    tputs(tgoto(tgetstr("do", NULL), line->x, line->y), 1, usefull);
    tputs(tgoto(tgetstr("cr", NULL), line->x, line->y), 1, usefull);
}

int     print_char(t_line *line)
{
    if (ft_strlen(line->str) == (line->str_len - 1))
        if (!realloc_line(line))
            exit(EXIT_FAILURE);
    if (line->cur == line->len)
    {
        line->cur++;
        line->str[line->len] = line->buf[0];
        line->x++;
        if (line->print)
        {
            write(1, &line->buf[0], 1);
            if (line->y == 0 && line->x == (line->winsize - line->offset))
                next_line(line);
            else if (line->y > 0 && line->x == line->winsize)
                next_line(line);
        }
    } else if (line->cur < line->len)
        insert_char(line);
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
    line->str[line->cur] = line->buf[0];
    while (tmp[j])
        line->str[i++] = tmp[j++];
    line->cur++;
    if (line->print)
    {
        line->x++;
        write(1, &line->buf[0], 1);
        write(1, tmp, ft_strlen(tmp));
    }
    old_pos(line, ft_strlen(tmp));
    ft_strdel(&tmp);
    return (1);
}