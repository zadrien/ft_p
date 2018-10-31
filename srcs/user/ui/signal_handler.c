/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 09:32:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/30 18:06:19 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"


void        check_signal(int signo)
{

}

void        signal_handler(void)
{
    int     i;

    i = -1;
    while (++ < 32)
    {
        signal(i, check_signal);
    }
}