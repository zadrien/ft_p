/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pi-utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:15:50 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 10:27:52 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

char    *ft_struct(char *cmd, t_token **arg)
{
    char    *line;
    t_token *tmp;

    line = ft_strdup(cmd);
    if ((tmp = *arg))
    {
        line = ft_strjoinf(line, " ", 1);
        while (tmp)
        {
            line = ft_strjoinf(line, tmp->str, 1);
            if (tmp->next)
                line = ft_strjoinf(line, " ", 1);
            tmp = tmp->next;
        }
    }
    return (line);
}

int     send_cmd(char *cmd, t_token **arg, int s)
{
    int     r;
    char    *line;
    t_token *tmp;

    r = 0;
    tmp = *arg;
    if ((line = ft_struct(cmd, &tmp)))
    {
        send(s, line, ft_strlen(line), 0);
        ft_strdel(&line);
        r = 1;
    }
    return (r);
}