/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:49 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/25 18:34:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

int     cm_left(t_line *line)
{
    if (line->x == 0 && line->cur > 0)
    {
        line->cur--;
        tputs(tgoto(tgetstr("le", NULL), line->x, line->y), 1, usefull);
    } else {

    }
    return (0);
}

int     cm_right(t_line *line)
{
    // int     len;

    // len = ft_strlen(line->str);
    if (line->cur < line->x)
    {
        line->cur++;
        tputs(tgoto(tgetstr("nd", NULL), line->x, line->y), 1, usefull);
    }
    return (0);
}