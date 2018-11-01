/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   login.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:11:53 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/28 14:10:53 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIN_H
# define LOGIN_H

#include "libft.h"

typedef struct      s_usr
{
    int             cs;
    char            *user;
    char            *password;
    char            *pwd;
    struct s_usr    *next;
}                   t_usr;

t_usr   *check_user(t_usr **lst, char *name);
void    finding_usr(t_usr **lst, int cs);
void    fork_client(t_usr **usr);

#endif