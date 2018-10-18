/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 11:11:41 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/12 16:27:11 by zadrien          ###   ########.fr       */
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

void    send_client(int fd, int cs)
{
    int     r;
    char    buf[8];
    struct stat stat;
    if (fork() == 0)
    {
        if (fstat(fd, &stat) == 0)
        {
            ft_putstr("Size of stream: ");
            ft_putnbr(stat.st_size);
            ft_putendl("");
        }
        while ((r = read(fd, buf, 7)) > 0)
        {
            buf[r] = '\0';
            send(cs, buf, ft_strlen(buf), 0);
        }
        send(cs, "0xff", 1, 0);
        exit(1);
    }
}

int     ft_list(t_token **lst, t_usr **usr, int cs)
{
    (void)usr;
    pid_t           pid;
    char            **exec;
    int             p[2];
    int             status;
    int             option = 0;
    struct rusage   rusage;

    ft_putendl_fd("LIST", 2);
    if (check_user(usr, cs) == 230)
    {
        exec = create_tab(&(*lst)->next);
        if (!pipe(p))
        {
            if ((pid = fork()) == 0)
            {
                close(p[0]);
                dup2(p[1], STDOUT_FILENO);
                execv(exec[0], exec);
            } else {
                close(p[1]);
                send_client(p[0], cs);
                close(p[0]);
                wait4(pid, &status, option, &rusage);
            }
        }
    }
    ft_putendl("End of listing");
    return (0);
}