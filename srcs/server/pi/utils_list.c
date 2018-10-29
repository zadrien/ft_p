/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:19:10 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 20:34:44 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

size_t     path_file(char *file)
{
    size_t  len;

    len = ft_strlen(file) - 1;
    ft_putstr("end char file name: ");ft_putchar(file[len]);ft_putendl("");
    while (file[len])
    {
        if (file[len] == '/')
            return (len);
        len--;
    }
    return (0);
}

int     handle_file(char *file, t_usr **usr)
{
    (void)usr;
    char    *path;
    size_t  len;

    ft_putendl("~~~handle_file~~~~");
    len = path_file(file);
    path = ft_strndup(file, len);
    ft_putendl(path);
    if (!chdir(path))
    {
        ft_strdel(&path);
        path = getcwd(NULL, 1023);
        chdir((*usr)->pwd);
        if (!ft_strncmp((*usr)->home, path, ft_strlen((*usr)->home)))
        {
            ft_strdel(&path);
            return (1);
        } else {
            ft_strdel(&path);
            return (501);
        }
    }
    return (550);
} // a finir mdr

int     handle_dir(char *dir, t_usr **usr)
{
    char    *path;
    ft_putendl("~~~handle_dir~~~~");
    if (!chdir(dir))
    {
        path = getcwd(NULL, 1023);
        chdir((*usr)->pwd);
        if (!ft_strncmp((*usr)->home, path, ft_strlen((*usr)->home)))
        {
            ft_strdel(&path);
            return (1);
        } else {
            ft_strdel(&path);
            return (501);
        }
    }
    return (550);
}

int     complete_tab(char **exec, t_token **lst)
{
    int     j;
    t_token *tmp;

    j = 1;
    tmp = *lst;
    while (tmp)
    {
        ft_putendl("!!!!");
        exec[j] = ft_strdup(tmp->str);
        tmp = tmp->next;
        j++;
    }
    exec[j] = NULL;
    return (1);
}