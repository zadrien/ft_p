/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 10:04:26 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/22 18:02:39 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

int     create_password(int s, char *pass)
{
    int     r;
    char    *line;
    char    buf[5] = "INIT\0";

    if (pass)
    {
        line = ft_strjoinf(buf, " ", 0);
        line = ft_strjoinf(line, pass, 1);
        send(s, line, ft_strlen(line), 0);
        r = get_code(s);
        if (r == 230)
        {
            ft_putendl_fd("Password created", 2);
            return (1);
        } else if (r == 332) {
            ft_putendl("Need account for login");
        } else {
            ft_putendl_fd("Password creation error", 2);
        }
    }
    return (0);
}

int     send_pass(int s, char *pass)
{
    char    *line;
    char    buf[5] = "PASS\0";

    if (pass) // cas chaine de caracter existe mais vide a gerer
    {
        line = ft_strjoin(buf, " ");
        line = ft_strjoinf(line, pass, 1);
        send(s, line, ft_strlen(line), 0);
        ft_strdel(&line);
        return (1);
    }
    return (0);
}

int enter_password(int s, int verify)
{
    int     r;
    char    *line;
    char    *line2;

    ft_putstr_fd("Enter password: ", 2);
    if (get_next_line(1, &line) > 0)
    {
        if (!verify)
        {
            send_pass(s, line);
            ft_strdel(&line);
            if (get_code(s) == 230)
            {
                ft_putendl_fd("Connection attempt success", 2);
                return (1);
            } else {
                ft_putendl_fd("Connection attempt fail", 2);
                ft_putendl_fd("Please write a correct password", 2);
                enter_password(s, 0);
            }
        } else {
            while (1) {
                ft_putstr_fd("Re-enter password: ", 2);
                if (get_next_line(1, &line2) > 0)
                {
                    if (!ft_strcmp(line, line2))
                    {
                        r = create_password(s, line);
                        ft_strdel(&line);
                        ft_strdel(&line2);
                        return (r);
                    }
                    else
                        ft_putendl("");
                    ft_strdel(&line2);
                } else {
                    ft_putendl_fd("ABORT", 2);
                }
            }
        }
    }
    return (0);
}

int     create_pass(t_token **lst, int s)
{
    t_token *tmp;

    tmp = *lst;
    if (ft_countarg(&tmp) == 1)
    {
        return (enter_password(s, 1));
    }
    return (0);
}

int     create_user(int s, char *name)
{
    int     r;
    char    *line;
    char    buf[6] = "CREAT\0";

    if (name)
    {
        line = ft_strjoinf(buf, " ", 0);
        line = ft_strjoinf(line, name, 1);
        send(s, line, ft_strlen(line), 0);
        r = get_code(s);
        if (r == 1)
        {
            return (enter_password(s, 1));
        } else if (r == 331) {
            ft_putendl_fd("Account already exist!", 2); 
            enter_password(s, 0);
        } else {
            ft_putendl_fd("Error occur", 2);
        }
    }
    return (0);
}

int     ask_create(int s, char *name)
{
    char    *line;

    ft_putstr_fd("Would you like to create it [Y/n]? ", 2);
    while (get_next_line(1, &line) > 0)
    {
        if (!ft_strcmp(line, "Y"))
        {
            ft_strdel(&line);
            if (create_user(s, name))
            {
                ft_putendl("user & password created");
                return (1);
            }
        }
        else if (!ft_strcmp(line, "n"))
        {
            ft_strdel(&line);
            break ;
        } else {
            ft_strdel(&line);
            ft_putendl("");
            ft_putstr_fd("Would you like to create it [Y/n]? ", 2);
        }
    }
    return (0);
} // possible leaks si Ctrl + D

int     auth(t_token **lst, int s)
{
    int     r;
    char    *line;
    char    buf[5] = "USER\0";
    t_token *tmp;

    tmp = (*lst)->next;
    if (tmp)
    {
        line  = ft_struct(buf, &tmp);
        send(s, line, ft_strlen(line), 0);
        ft_strdel(&line);
        r = get_code(s);
        if (r == 331)
        {
            ft_putendl_fd("Valid username", 2);
            if (enter_password(s, 0))
                return (1);
        } else if (r == 332)
            return (ask_create(s, tmp->str));
    }
    return (0);
}