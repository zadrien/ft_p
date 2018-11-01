/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lpwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:31:49 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 10:20:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ftp.h"

int    ft_lpwd(t_token **lst, int socket)
{
    (void)socket;
    char    buf[1024];
    t_token *tmp;

    if (*lst)
    {
        tmp = *lst;
        if (tmp->next)
            ft_putendl_fd("lpwd: too many arguments", 2);
        else {
            getcwd(buf, 1023);
            ft_putendl(buf);
            return (1);
        }
    }
    return (0);
}

int    ft_pwd(t_token **lst, int s)
{
    int     r;
    char    buf[4] = "PWD\0";
    t_token *tmp;

    tmp = (*lst)->next;
    if (!tmp)
    {
        if (send_cmd(buf, &tmp, s))
            if ((r = wait_server(s, NONE, PRINT, GET)) == 226)
                return (1);
    } else
        ft_putendl_fd("pwd: too many arguments", 2);
    return (0);
}