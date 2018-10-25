/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:38:42 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/25 18:18:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

t_line  *init_line(int offset)
{
    t_line *tmp;
    if (!(tmp = (t_line*)malloc(sizeof(t_line))))
        return (NULL);
    if (!(tmp->str = (char*)malloc(sizeof(char) * 50)))
        return (NULL);
    ft_bzero(tmp->str, 50);
    tmp->len = 50;
    tmp->x = 0;
    tmp->y = 0;
    tmp->cur = 0;
    tmp->max = window_size();
    tmp->offset = offset;
    return (tmp);
}

void    change_value(t_edit **edit, int i)
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
}

int     init_term(t_edit **edit, int i)
{
    t_edit  *tmp;

    tmp = *edit;
    if (tmp)
    {
        if (tgetent(NULL, tmp->name_term) == -1)
            return (-1);
        if (tcgetattr(0, &(tmp)->term) == -1)
            return (-1);
        change_value(&tmp, i);
        if (tcsetattr(0, TCSANOW, &(tmp)->term) == -1)
            return (-1);
        return (1);
    }
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