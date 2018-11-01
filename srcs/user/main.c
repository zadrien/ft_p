/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:35:53 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 08:33:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

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

void    success_error(char *str, char *color)
{
    ft_putstr_fd(color, 2);
    ft_putendl_fd(str, 2);
    ft_putstr_fd(RESET, 2);
}

void    start_line(t_edit *term, int socket, int printable, char *prompt)
{
    int     r;
    t_line  *line;

    line = init_line(ft_strlen(prompt), printable);
    ft_putstr_fd(prompt, 2);
    while (1)
    {
        ft_memset(line->buf, '\0', 6);
        if (read(0, line->buf, 6) == 0)
            break ;
        if (keyboard(line))
        {
            if ((r = userPI(line->str, socket)) == -1)
                break ;
            else 
                success_error((r == 1 ? "success" : "error"), (r == 1 ? GREEN : RED));
            mode_on(term);
            restore_value(line);
            ft_putstr_fd(prompt, 2);
        }
    }
    free_line(line);
}

int     main(int ac, char **av)
{
    int     r;
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
        if ((socket = com_link(av[1], av[2])) > 0)
        {
            if ((r = get_code(socket)) == 220) 
            {
                print_msg("Connection Establishment success.. Please login.", GREEN, 2);
                start_line(term, socket, ON, "$> ");
            }
            else if (r == 421) {
                print_msg("Service not avalaible, closing control connection", RED, 2);
            }
        }
    }
    close(socket);
    free(term);
    
}