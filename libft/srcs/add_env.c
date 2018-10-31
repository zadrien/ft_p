/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:00:05 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/20 13:35:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     add_env(t_env **env, char **var)
{
    (*env)->var = ft_strdup(var[0]);
    (*env)->value = var[1] ? ft_strdup(var[1]) : NULL;
    return (1);
}


// int     add_env(t_env **env, char *var, char *val)
// {
//     t_env *tmp;
//     t_env   *new;

//     if (!(new = (t_env*)malloc(sizeof(t_env))))
//         return -1;
//     new->var = ft_strdup(var);
//     new->value = val ? ft_strdup(val) : NULL;
//     new->next = NULL;

//     if (*env)
//     {
//         tmp = *env;
//         while (tmp->next)
//             tmp = tmp->next;
//         tmp->next = new;
//         /*
//         if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
//             return (-1);
//         tmp = tmp->next;
//         tmp->var = ft_strdup(var);
//         tmp->value = val ? ft_strdup(val) : NULL;
//         tmp->next = NULL;
//         */
//     } else {
//         env = &new;
//         /*
//         if (!((*env) = (t_env*)malloc(sizeof(t_env))))
//             return (-1);
//         (*env)->var = ft_strdup(var);
//         (*env)->value = val ? ft_strdup(val) : NULL;
//         (*env)->next = NULL;
//         */
//     }
//     return (1);
// }
