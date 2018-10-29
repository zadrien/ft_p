/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 08:07:24 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 16:35:19 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int     go_home(t_usr **usr)
{
    t_usr *tmp;

    tmp = *usr;
    if (!ft_strcmp(tmp->pwd, tmp->home))
        return (250);
    else {
        if (chdir(tmp->home) == 0)
        {
            ft_strdel(&tmp->pwd);
            tmp->pwd = ft_strdup(tmp->home);
            return (250);
        }
    }
    return (550);
}

int     go_dir(t_token **dir, t_usr **usr)
{
    char    *path;
    t_usr   *tmp;

    tmp = *usr;
    if ((*dir)->str)
    {
        path = ft_strjoinf(tmp->pwd, "/", 0);
        path = ft_strjoinf(path, (*dir)->str, 1);
        if (chdir(path) == 0)
        {
            ft_strdel(&path);
            path = getcwd(NULL, 1023);
            if (!ft_strncmp(tmp->home, path, ft_strlen(tmp->home)))
            {
                ft_strdel(&tmp->pwd);
                tmp->pwd = ft_strdup(path);
                ft_strdel(&path);
                return (250);
            }else {
                chdir(tmp->pwd);
            }
        }
        ft_strdel(&path);
    }
    return (550);
}

int     cwd(t_token **lst, t_usr **usr)
{
    int     nb;
    t_token *tmp;

    if ((*usr)->password == 0)
        return (530);
    if ((tmp = *lst))
    {
        if ((nb = ft_countarg(&tmp)) == 2)
        {
            ft_putendl("2 arguments");
            if (tmp->next->str && !ft_strcmp(tmp->next->str, "/"))
                return (go_home(usr));
            return (go_dir(&tmp->next, usr));
        } else if (nb == 1) {
            return (go_home(usr));
        }
    }
    return (501);
}

char	*get_path(const char *big, const char *little)
{
	int	i;
	int	j;

    i = -1;
	if (little[0] == '\0')
		return ((char *)big);
    while (big[++i])
    {
        j = 0;
        while (little[j] == big[i + j])
            if (little[++j] == '\0')
                return ((char *)big + (i + j));
    }
    return (0);
}

int     ft_pwd(t_token **lst, t_usr **usr)
{
    int     cs;
    char    *str;
    t_usr   *tmp;

    tmp = *usr;
    if ((*usr)->password == 0)
        return (530);
    if (!(*lst)->next)
    {
        cs = transmission(*usr, GET, 0);
        str = get_path(tmp->pwd, tmp->home);
        ft_putendl("===PWD===");
        ft_putendl(str);
        return (send_str(cs, str[0] != '\0' ? str : "/"));
    }
    return (226);
}