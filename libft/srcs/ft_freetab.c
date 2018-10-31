/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:21:21 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 16:23:39 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_freetab(char **trash)
{
    int     i;

    i = -1;
    if (!trash)
        return ;
    while (trash[++i])
        ft_strdel(&trash[i]);
    free(trash);
}