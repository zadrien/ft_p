/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 08:36:53 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 09:06:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

int     ft_cwd(t_token **lst, int s)
{
    char    buf[4] = "CWD\0";
    char    *line;

    line = ft_struct(buf, &(*lst)->next);
    send(s, line, ft_strlen(line), 0);
    ft_strdel(&line);
    return (wait_response(s, 1));
}