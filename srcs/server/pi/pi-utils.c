/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pi-utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:15:50 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/20 15:17:48 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

char    *ft_struct(char *cmd, t_token **arg)
{
    char    *line;
    t_token *tmp;

    line = ft_strdup(cmd);
    if ((tmp = *arg))
    {
        line = ft_strjoinf(line, " ", 1);
        while (tmp)
        {
            line = ft_strjoinf(line, tmp->str, 1);
            if (tmp->next)
                line = ft_strjoinf(line, " ", 1);
            tmp = tmp->next;
        }
    }
    ft_putendl(line);
    return (line);
}