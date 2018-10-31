/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:24:17 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/30 17:53:12 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int     ft_put(t_token **lst, int s) // Cote client
{
    t_token     *tmp;
    char        *line;
    char        buf[5] = "STOU\0";

    tmp = (*lst)->next;
    if (ft_countarg(tmp->next) == 1)
    { // verification du nom du ficher necessaire
        line = ft_struct(buf, tmp);
        send(s, line, ft_strlen(line), 0);
        if (get_code(s) == 150) // si le fichier est creer cote serveur 
        {
           transmission() 
        }
    }
}

int     put_server(t_token **lst, t_usr **usr) // Cote serveur
{
    int         fd;
    t_usr       *ustmp;
    t_token     *tmp;

    tmp = *lst;
    ustmp = *usr;

    if ((fd = open(file, O_APPEND | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
    {
        recept(ustmp->cs, fd, NONE);
    }
}