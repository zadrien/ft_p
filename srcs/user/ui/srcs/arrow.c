/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:49 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/26 17:21:32 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

int     cm_left(t_line *line)
{
    if (line->y == 0)
    {
        if (line->cur > 0)
        {
            line->cur--;
            line->x--;
            tputs(tgoto(tgetstr("le", NULL), line->x, line->y), 1, usefull);
        }
    } else if (line->y > 0) {
        line->cur--;
        if (line->x == 0)
        {
            line->y--;
            if (line->y == 0)
            {
                line->x = line->max - line->offset;
            } else {
                line->x = line->max;
            }
            line->x--;
            tputs(tgoto(tgetstr("up", NULL), line->x, line->y), 1, usefull);
            replace_cursor(line, END);           
        } else {
            line->x--;
            tputs(tgoto(tgetstr("le", NULL), line->x, line->y), 1, usefull);            
        }
    }
    return (0);
}

int     cm_right(t_line *line)
{
    if (line->cur < line->len) // here bug to fix
    {
        line->cur++;
        if (line->y == 0)
        {
            if (line->x < (line->max - line->offset))
            {
                line->x++;
                tputs(tgoto(tgetstr("nd", NULL), line->x, line->y), 1, usefull);
            }
            if (line->x == (line->max - line->offset))
            {
                line->y++;
                line->x = 0;
                tputs(tgoto(tgetstr("do", NULL), line->x, line->y), 1, usefull);
                tputs(tgoto(tgetstr("cr", NULL), line->x, line->y), 1, usefull);
            }
        } else if (line->y > 0) {
            if (line->x == line->max)
            {
                line->x = 0;
                line->y++;
                tputs(tgoto(tgetstr("do", NULL), line->x, line->y), 1, usefull);
                tputs(tgoto(tgetstr("cr", NULL), line->x, line->y), 1, usefull);
            } else {
                line->x++;
                tputs(tgoto(tgetstr("nd", NULL), line->x, line->y), 1, usefull);
            }
        }
    }
    return (0);
}

int     del_char(t_line *line)
{
    char    *tmp;
    size_t  i;
    size_t  j;

    // printf("BONJOUR\n");
    if (line->cur <= line->len && line->cur > 0) // cas in-line
    {
        tmp = ft_strdup(line->str + line->cur);
        // printf("\ntmp=%s\n", tmp);
        j = -1;
        i = line->cur - 1;
        // cm_left(line);
        // printf("charactere to delete=%c\n", line->str[line->cur]);
        while (tmp[++j])
        {
            // write(1, &tmp[j], 1);
            line->str[i] = tmp[j];
            i++;
        }
        line->str[i] = '\0';
        cm_left(line);
        write(1, tmp, ft_strlen(tmp));
        write(1, " ", 1);
        // line->cur += i;
        multi_pos(line, ft_strlen(tmp) + 1); // change function for deletion
        ft_strdel(&tmp);
        line->len--;
    } else {
        // printf("LOL\n");
    }
    return (0);
}