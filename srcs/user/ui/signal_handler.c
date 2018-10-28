/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 09:32:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/28 09:34:01 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"


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