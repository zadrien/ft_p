/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lls.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:27:35 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/28 10:55:16 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

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

void    init_fork(pid_t pid)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
    if (setpgid(pid, pid) < 0)
        exit(EXIT_FAILURE);
    tcsetpgrp(g_shell_terminal, pid);
}

void    init_parent(pid_t child)
{
    setpgid(child, child);
    tcsetpgrp(g_shell_terminal, child);
}

void    restore_parent()
{
    tcsetpgrp(g_shell_terminal, g_shell_pgid);
    tcsetattr(g_shell_terminal, TCSADRAIN, &g_shell_termios);
}

int     ft_lls(t_token **lst, int socket)
{
    (void)socket;
    pid_t   pid;
    char    **exec;
    int     status;
    // int     option = 0;
    struct rusage rusage;

    exec = create_tab(&(*lst)->next);
    if ((pid = fork()) == 0)
    {
        init_fork(getpid());
        execv(exec[0], exec);
    } else {
        init_parent(pid);
        wait4(pid, &status, WUNTRACED | WCONTINUED, &rusage);
        restore_parent();
    }
    if (WIFEXITED(status) && !WEXITSTATUS(status))
        return (1);
    return (0);
}