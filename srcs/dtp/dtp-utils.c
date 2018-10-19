/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:14:00 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/19 16:26:31 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtp.h"

int    get_code(int s)
{
    int     r;

    recv(s, &r, sizeof(int), 0);
    ft_putnbr(r);ft_putendl("");
    return (r);
}

void    send_code(int s, int code)
{
    send(s, &code, sizeof(int), 0);
}