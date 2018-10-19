/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 11:11:41 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/19 15:50:57 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char    **create_tab(t_token **lst)
{
    int     i;
    int     j;
    char    **cmd;
    t_token *tmp;

    j = 1;
    i = 2;
    if ((*lst))
        i += ft_countarg(lst);
    if (!(cmd = (char**)malloc(sizeof(char*) * i)))
        return (NULL);
    cmd[0] = ft_strdup("/bin/ls");
    if (i > 2)
    {
        tmp = *lst;
        while (tmp)
        {
            cmd[j] = ft_strdup(tmp->str);
            tmp = tmp->next;
            j++;
        }
    }
    cmd[j] = NULL;
    return (cmd);
}

// void    send_client(int fd, t_usr *usr)
// {
//     if (fork() == 0)
//     {
//         ascii_mode(usr);
//         exit(-1);
//     }
// }

int     ft_list(t_token **lst, t_usr **usr)
{
    pid_t           pid;
    char            **exec;
    int             sock;
    // int             p[2];
    int             status;
    int             option = 0;
    struct rusage   rusage;
    t_usr           *tmp;

    tmp = *usr;
    ft_putendl_fd("LIST", 2);
    if (check_user(usr, tmp->cs) == 230)
    {
        exec = create_tab(&(*lst)->next);
        // if (!pipe(p))
        // {
            if (sock = ascii_mode(tmp))
            {
                if ((pid = fork()) == 0)
                {
                    // close(p[0]);
                    dup2(sock, STDOUT_FILENO);
                    execv(exec[0], exec);
                } else {
                    // close(p[1]);
                    // send_client(p[0], tmp);
                    // close(p[0]);
                    wait4(pid, &status, option, &rusage);
                }
                close(sock);
            }
        // }
    }
    // write(tmp->cs, '\0', 1);
    ft_putendl("End of listing");
    return (0);
}