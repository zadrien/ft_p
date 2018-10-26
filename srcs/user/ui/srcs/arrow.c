/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:49 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/26 12:03:24 by zadrien          ###   ########.fr       */
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