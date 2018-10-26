/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 18:28:08 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/26 06:44:56 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

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
    } else if (line->cur < line->len) {
        insert_char(line);
        // reposition le curseur apres la lettre ajouter
    }
    // else if (line->cur > line->len) {
    //     line->str[line->x] = line->buf[0];
    //     line->x++;
    //     line->cur++;
    //     write(1, &line->buf[0], 1);
    // }
    if (line->y == 0 && line->x == (line->max - line->offset))
    {
        tputs(tgoto(tgetstr("do", NULL), line->x, line->y), 1, usefull);
        tputs(tgoto(tgetstr("cr", NULL), line->x, line->y), 1, usefull);
        line->x = 0;
        line->y++;
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
    replace_cursor(line, AR_LEFT);
    line->x++;
    line->cur++;
    ft_strdel(&tmp);
    return (1);
}

int     replace_cursor(t_line *line, int mode)
{
    size_t     i;

    if (mode == AR_LEFT)
    {
        i = line->x;
        while (i > line->cur)
        {
            tputs(tgoto(tgetstr("le", NULL), line->x, line->y), 1, usefull);
            i--;
        }
    } else if (mode == END) {
        i = 0;
        while (++i < line->max)
            tputs(tgoto(tgetstr("nd", NULL), line->x, line->y), 1, usefull);

        // if (line->cur < line->x)
        //     while (line->cur < line->x)
        //     {
        //         tputs(tgoto(tgetstr("nd", NULL), line->x, line->y), 1, usefull);
        //         line->cur++;
        //     }
    }
    return (1);
}