/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put-client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 15:08:09 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/21 15:45:27 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

int     c_put(t_token **lst, int s)
{
    int     fd;
    char    *line;
    char    buf[5] = "STOU\0";
    t_token *tmp;

    tmp = (*lst)->next;
    if (ft_countarg(&tmp) == 1)
    {
        ft_putendl(tmp->str);
        if ((fd = open(tmp->str, O_RDONLY)))
        {
            line = ft_struct(buf, &tmp);
            send(s, line, ft_strlen(line), 0);
            return (wait_server(s, fd, NONE, PUT));
        }
    }
    return (0);
}