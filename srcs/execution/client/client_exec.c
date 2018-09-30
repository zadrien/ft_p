/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 11:33:04 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/30 16:13:06 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void    ft_quit(t_token **lst, int socket)
{
    free_token(lst);
    close(socket);
    exit(0);
}

int     client_exec(char *str, int socket)
{
    int     i;
    t_token   *tok;
    static const t_client   cmd[5] = {{"lcd", &ft_lcd}, {"lpwd", &ft_lpwd},
    {"lls", &ft_lls}, {"quit", &ft_quit}, {"get", &ft_lget}};

    i = -1;
    tok = parser(str);
    while (++i < 5)
    {
        if (!ft_strcmp(cmd[i].cmd, tok->str))
        {
            cmd[i].f(&tok, socket);
            return (1);
        }
    }
    if (i == 5)
    {
        free_token(&tok);
        ft_putendl("Send to server");
        // send_server(str);
    }
    return (0);
}