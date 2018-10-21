/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get-client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 11:57:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/21 15:20:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

int     c_get(t_token **lst, int s)
{
    int     fd;
    char    *line;
    char    buf[5] = "RETR\0";
    t_token *tmp;
    
    tmp = (*lst)->next;
    if (ft_countarg(&tmp) == 1)
    {
        if ((fd = open(tmp->str, O_APPEND | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
        {
            line = ft_struct(buf, &tmp);
            send(s, line, ft_strlen(line), 0);
            ft_strdel(&line);
            return (wait_server(s, fd, NONE, GET));
        }
    }
    return (0);
}