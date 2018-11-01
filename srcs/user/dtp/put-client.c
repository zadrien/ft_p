/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put-client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 15:08:09 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 16:36:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int     c_put(t_token **lst, int s)
{
    int     r;
    int     fd;
    char    *line;
    char    buf[5] = "STOU\0";
    t_token *tmp;

    tmp = (*lst)->next;
    if (ft_countarg(&tmp) == 1)
    {
        if ((fd = open(tmp->str, O_RDONLY)) > 0)
        {
            ft_putendl_fd("Transfering file to server..", 2);
            ft_putstr_fd("File name: ", 2);
            ft_putendl_fd(tmp->str, 2);
            line = ft_struct(buf, &tmp);
            send(s, line, ft_strlen(line), 0);
            r = wait_server(s, fd, NONE, PUT);
            return (get_error(r, fd));
        } else {
            ft_putstr_fd(RED, 2);
            ft_putendl_fd("put: error: file not found", 2);
            ft_putstr_fd(RESET, 2);
        }
    }
    return (0);
}