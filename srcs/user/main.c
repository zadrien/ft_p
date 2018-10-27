/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:35:53 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/27 14:44:53 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

void usage(char *str)
{
    ft_putstr_fd(str, 2);
    ft_putendl_fd(" <addr> <port>", 2);
    exit(-1);
}

char    *cmd_line()
{
    char    *line;

    ft_putstr_fd("$> ", 2);
    if (get_next_line(1, &line) > 0)
        return (line);
    return (NULL);
}

// int     main(int ac, char **av)
// {
//     int     socket;
//     char    *line;

//     if (ac != 3)
//         usage(av[0]);
//     socket = com_link(av[1], av[2]);
//     while (1)
//     {
//         ft_putendl("LOOP");
//         line = cmd_line();
//         if (userPI(line, socket))
//             ft_putendl_fd("SUCCESS", 2);
//         else
//             ft_putendl_fd("ERROR", 2);
//         ft_strdel(&line);
//     }
//     return (0);
// }

int     main(int ac, char **av)
{
    int     socket;
    t_edit  *term;

    if (ac != 3)
        usage(av[0]);
    if (!(term = init_cmd_line()))
    {
        ft_putendl_fd("Failed init command line", 2);
        return (0);
    }
    if (init_term(term))
    {
        socket = com_link(av[1], av[2]);
        start_line(term, socket, ON, "$> ");
    }
    
}