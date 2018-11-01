/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 10:04:26 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 10:58:54 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

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
        line = ft_strjoinf(buf, " ", 0);
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
    t_line  *line;
    t_line  *line2;

    if ((line = get_line("Enter password: ", OFF)))
    {
        if (!verify)
        {
            send_pass(s, line->str);
            free_line(line);
            if ((r = get_code(s)) == 230)
            {
                print_msg("Connection attempt success", GREEN, 2);
                return (1);
            } else if (r == 650) {
                print_msg("Can't find password for this account..\nPlease create it.", RED, 2);
                return (enter_password(s, 1));
            } else if (r == 550) {
                print_msg("Request action not taken, no access.", RED, 2);
            } else {
                print_msg("Connection attempt fail..\nPlease write a correct password", RED, 2);
                return (enter_password(s, 0));
            }
        } else {
            while (1)
            {
                if ((line2 = get_line("Re-enter password: ", OFF)))
                {
                    if (!ft_strcmp(line->str, line2->str))
                    {
                        r = create_password(s, line->str);
                        free_line(line);
                        free_line(line2);
                        return (r);
                    }
                    else
                        ft_putendl("Not the same password");
                    free_line(line2);
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
        return (enter_password(s, 1));
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
        ft_strdel(&line);
        r = get_code(s);
        if (r == 1 || r == 331)
        {
            if (r == 331)
                print_msg("Account already exist, please enter password..", RED, 2); // Hmmm ?
            return (enter_password(s, r == 331 ? 0 : 1));
        } else if (r == 230){
            print_msg("Already logged in.", RED, 2);
        } else {
            ft_putendl_fd("Error occur", 2);
        }
    }
    return (0);
}

int     ask_create(int s, char *name)
{
    t_line  *line;

    while ((line = get_line("Would you like to create it? [Y/n]:", ON)))
    {
        if (!ft_strcmp(line->str, "Y"))
        {
            free_line(line);
            if (create_user(s, name))
            {
                print_msg("Account created and logged in", GREEN, 2);
                return (1);
            }
        }
        else if (!ft_strcmp(line->str, "n"))
        {
            free_line(line);
            break ;
        } else {
            free_line(line);
            ft_putendl("");
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
        if ((r = get_code(s)) == 331)
        {
            line = ft_strjoinf("Password required for ", tmp->str, 0);
            print_msg(line, GREEN, 2);
            ft_strdel(&line);
            if (enter_password(s, 0))
                return (1);
        } else if (r == 332) {
            line = ft_strjoinf(tmp->str, " doesn't exist.", 0);
            print_msg(line, RED, 2);
            ft_strdel(&line);
            return (ask_create(s, tmp->str));
        }
    }
    return (0);
}