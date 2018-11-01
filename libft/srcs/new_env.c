/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 10:59:22 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 11:29:18 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env   *new_env(char **env)
{
    int     i;
    char    **arr;
    t_env   *start;
    t_env   *tmp;

    i = -1;
    if (!env)
        return (NULL); // create new env with pwd variable only
    if (!(start = (t_env*)malloc(sizeof(t_env))))
        return (NULL);
    tmp = start;
    while (env[++i])
    {
        if ((arr = ft_strsplit(env[i], '=')))
        {
            if (add_env(&tmp ,arr))
                if (env[i + 1])
                {
                    if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
                        return (NULL);
                    tmp = tmp->next;
                }
        }
    }
    tmp->next = NULL;
    return (start);
}

