/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lpwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:31:49 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/27 13:05:11 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ftp.h"

void    ft_lpwd(t_token **lst, int socket)
{
    (void)socket;
    char    buf[1024];
    t_token *tmp;

    if (*lst)
    {
        tmp = *lst;
        if (tmp->next)
            return (ft_putendl_fd("pwd: too many arguments", 2));
        getcwd(buf, 1023);
        return (ft_putendl(buf));
    }
}