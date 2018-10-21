/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lls.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:27:35 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/21 12:33:26 by zadrien          ###   ########.fr       */
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

int     ft_lls(t_token **lst, int socket)
{
    (void)socket;
    pid_t   pid;
    char    **exec;
    int     status;
    // int     option = 0;
    struct rusage rusage;

    ft_putendl_fd("lls", 2);
    exec = create_tab(&(*lst)->next);
    if ((pid = fork()) == 0)
    {
        execv(exec[0], exec);
    } else {
        wait4(pid, &status, WUNTRACED | WCONTINUED, &rusage);
    }
    if (WIFEXITED(status) && !WEXITSTATUS(status))
        return (1);
    return (0);
}