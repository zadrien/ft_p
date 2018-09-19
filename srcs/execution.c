/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:58:31 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/19 15:19:27 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

typedef struct      s_builtin
{
    char            *cmd;
    int             (*f)();
}                   t_builtin;

void    execution(char *str)
{
    t_token *tok;
    t_token *tmp;

    ft_putstr("Client send: ");
    ft_putendl(str);
    tok = parser(str);
    if (tok) {
        tmp = tok;
        while (tmp) {
            ft_putendl(tmp->str);
            tmp = tmp->next;
        }
    } else {
        ft_putendl_fd("token is null", 2);
    }
}