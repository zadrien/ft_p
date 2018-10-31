/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:58:44 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 16:46:28 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void    progress_bar(void)
{
    size_t  i;

    i = 1;
    ft_putstr_fd(RED, 2);
    ft_putstr_fd("[", 2);
    ft_putstr_fd(RESET, 2);
    tputs(tgoto(tgetstr("sc", NULL), 0, 0), 1, usefull);
    tputs(tgetstr("vi", NULL), 1, usefull);
    while(i++ < g_win)
        tputs(tgoto(tgetstr("nd", NULL), 0, 0), 1, usefull);
    ft_putstr_fd(GREEN, 2);
    ft_putstr_fd("]", 2);
    ft_putstr_fd(RESET, 2);
    tputs(tgoto(tgetstr("rc", NULL), 0, 0), 1, usefull);
}

int    replace_curs(off_t tot, off_t size)
{
    tputs(tgetstr("ve", NULL), 1, usefull);
    tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, usefull);
    tputs(tgoto(tgetstr("cr", NULL), 0, 0), 1, usefull);
    if (tot == size)
    {
        ft_putstr_fd(GREEN, 2);
        ft_putendl_fd("Transfer complete", 2);
        ft_putstr_fd(RESET, 2);
        return (250);
    } else {
        ft_putstr_fd(RED, 2);
        ft_putendl_fd("Transfer error", 2);
        ft_putstr_fd(RESET, 2);
    }
    return (426);
}

void    print_progress(off_t tot, off_t size)
{
    size_t   r;
    size_t   i;

    r = ((size_t)tot * 100) / (size_t)size;
    r = ((g_win - 3) * r) / 100;
    if (r == 1)
    {
        write(1, ">", 1);
        tputs(tgoto(tgetstr("rc", NULL), 0, 0), 1, usefull);
    } else if (r > 1) {
        i = -1;
        while (++i < r)
            write(1, "=", 1);
        if (i == r)
            write(1, ">", 1);
        tputs(tgoto(tgetstr("rc", NULL), 0, 0), 1, usefull);        
    }
}

int     get_info(int s)
{
    off_t   size;
    
    ft_putstr_fd("Size file: ", 2);
    recv(s, &size, sizeof(off_t), 0);
    ft_putendn(size);
    return (size);
}