/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 11:11:41 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 20:42:12 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void    print_tab(char **exec);

int     verify_path(char *cwd, char *file, t_usr **usr)
{
    int         r;
    char        *path;
    struct  stat buf;

    r = 0;
    path = ft_strjoinf(cwd, file, 0);
    ft_putendl("====verify path====");
    ft_putendl(path);
    if (path)
    {
        if (!stat(path, &buf))
        {
            if (S_ISREG(buf.st_mode))
                r = handle_file(path, usr);
            else
                r = handle_dir(path, usr);
        } else {
            ft_putendl_fd("FAILURE", 2);
        }
    }
    ft_strdel(&path);
    return (r);
}

int     check(char **str, char *cwd, t_usr **usr)
{
    int     r;

    if (*str)
    {
        if (!ft_strcmp(*str, "/"))
        {
            ft_strdel(str);
            *str = ft_strdup((*usr)->home);
            return (1);
        } else {
            if ((r = verify_path(cwd, *str, usr)) == 1)
            {
                ft_putendl(*str);
                // *str = ft_strjoinf(cwd, *str, 2);
                // ft_putendl("==arg==");
                // ft_putendl(*str);
                return (1);
            } else if (r == 501 || r == 550) {
                return (r);
            }
        }
    }
    ft_putendl("?????check");
    return (451);
}

int     verify_arg(t_token **lst, t_usr **usr)
{
    int     r;
    char    *cwd;
    t_token *tmp;

    tmp = (*lst)->next;
    if (tmp)
    {
        cwd = ft_strjoinf((*usr)->pwd, "/", 0);
        while (tmp)
        {
            if (tmp->str[0] != '-')
                if ((r = check(&tmp->str, cwd, usr)) == 501 || r == 550 || r == 451)
                {
                    ft_strdel(&cwd);
                    return (r);
                }
            tmp = tmp->next;
        }
        ft_strdel(&cwd);
    }
    return (0);
}

char    **create_tab(t_token **lst)
{
    int     j;
    int     i;
    char    **cmd;
    t_token         *tmp;

    j = 1;
    i = 2;
    if ((*lst))
        i += ft_countarg(lst);
    if (!(cmd = (char**)malloc(sizeof(char*) * i)))
        return (NULL);
    tmp = *lst;
    cmd[0] = ft_strdup("/bin/ls");
    while (tmp)
    {
        cmd[j] = ft_strdup(tmp->str);
        tmp = tmp->next;
        j++;
    }
    cmd[j] = NULL;
    return (cmd);
} // verify path access granted

int     ft_ls(char **exec, t_usr **usr)
{
    int             sock;
    int             status;
    int             option = 0;
    pid_t           pid;
    t_usr           *tmp;
    struct rusage   rusage;

    tmp = *usr;
    if ((sock = transmission(tmp, GET, NONE)) > 0)
    {
        // print_tab(exec);
        // ft_putstr("socket value: ");ft_putendn(sock);
        if (sock == 425)
            return (sock);
        if ((pid = fork()) == 0)
        {
            dup2(sock, STDOUT_FILENO); // a revoir not RFC 959 compatible.. 8bit package
            execv(exec[0], exec);
        } else {
            wait4(pid, &status, option, &rusage);
            close(sock);
            return (226);
        }
    }
    return (0); // can't open data connection
}

void    print_tab(char **exec)
{
    int     i;

    i = -1;
    while (exec[++i])
        ft_putendl(exec[i]);
}

int     ft_list(t_token **lst, t_usr **usr)
{
    int             r;
    char            **exec;
    t_usr           *tmp;

    tmp = *usr;
    if (tmp->password == 0)
        return (530);
    if ((r = verify_arg(lst, usr)) != 0)
        return (r);
    ft_putendl("==MARYNE==");
    if ((exec = create_tab(&(*lst)->next)))
    {
        ft_putendl("PASS");
        r = ft_ls(exec, usr);
        ft_freetab(exec);
        return (r);
    } else
        return (501);
    ft_putendl("End of listing");
    return (0);
}