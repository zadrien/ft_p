/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 10:59:22 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/20 13:35:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env   *new_env(char **env)
{
    int     i;
    char    **tab;
    t_env   *start;
    t_env   *tmp;

    i = -1;
    if (!env)
        return (NULL);
    if (!(start = (t_env*)malloc(sizeof(t_env))))
        return (NULL);
    tmp = start;
    while (env[++i])
    {
        if ((tab = ft_strsplit(env[i], '=')))
        {
            if (add_env(&tmp ,tab))
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
// t_env   *new_env(char **env)
// {
//     int     i;
//     char    **tab;
//     t_env   *start;

//     i = -1;
//     start = NULL;
//     if (!env)
//         return (NULL);
//     while (env[++i])
//     {
//         if ((tab = ft_strsplit(env[i],'=')))
//             if(add_env(&start, tab[0], tab[1]))
//             {
//                 ft_strdel(&tab[0]);
//                 ft_strdel(&tab[1]);
//                 free(tab);
//             }
//     }
//     return (start);
// }
