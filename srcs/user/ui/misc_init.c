/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:50:20 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/30 18:06:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int     usefull(int i)
{
    return (write(2, &i, 1));
}

int     window_size(void)
{
    struct winsize ws;

    if (ioctl(0, TIOCGWINSZ, &ws) == -1)
        return (0);
    return (ws.ws_col);
}