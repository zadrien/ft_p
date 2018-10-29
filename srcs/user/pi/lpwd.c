/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lpwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:31:49 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 09:56:30 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "user.h"

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
    char    buf[4] = "PWD\0";
    char    *line;
    t_token *tmp;

    tmp = (*lst)->next;
    if (!tmp)
    {
        line = ft_struct(buf, &tmp);
        send(s, line, ft_strlen(line), 0);
        ft_strdel(&line);
        return (wait_response(s, 1));// put to 1;
    } else
        ft_putendl_fd("pwd: too many arguments", 2);
    return (0);
}