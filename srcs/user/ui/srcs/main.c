/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:37:50 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/24 19:18:27 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"


int     usefull(int i)
{
    return (write(2, &i, 1));
}

void    cursor_display(int mod)
{
    tputs(tgetstr((mod ? "ve" : "vi"), NULL), 1, usefull);
}

void    change_value(t_edit **edit, int i)
{
    t_edit  *tmp;

    tmp = *edit;
    if (i)
    {
        tmp->term.c_lflag &= ~(ICANON | ECHO);
        tmp->term.c_cc[VMIN] = 1;
        tmp->term.c_cc[VTIME] = 0;
    } else if (i == 0)
    {
        tmp->term.c_lflag |= ~(ICANON | ECHO);
        tmp->term.c_cc[VMIN] = 1;
        tmp->term.c_cc[VTIME] = 0;
    }
}

int     init_term(t_edit **edit, int i)
{
    t_edit  *tmp;

    tmp = *edit;
    if (tmp)
    {
        if (tgetent(NULL, tmp->name_term) == -1)
            return (-1);
        if (tcgetattr(0, &(tmp)->term) == -1)
            return (-1);
        change_value(&tmp, i);
        if (tcsetattr(0, TCSANOW, &(tmp)->term) == -1)
            return (-1);
        return (1);
    }
    return (0);
}

t_edit     *init_cmd_line(void)
{
    t_edit  *tmp;

    if (!(tmp = (t_edit*)malloc(sizeof(t_edit))))
        return (NULL);
    if (!(tmp->line = (char*)malloc(sizeof(char) * 50)))
        return (NULL);
    ft_bzero(tmp->line, 50);
    if ((tmp->name_term = getenv("TERM")) == NULL)
        return (NULL);
    return (tmp);
}

int     get_key(void)
{
    int     r;
    char    buf[5];

    r = read(0, buf, 4);
    buf[r] = '\0';
    return (*(int*)buf);
}

int     motion(t_edit **line, int   key)
{
    t_edit  *tmp;
    tmp = *line;
    if (key == ??)
    {

    } else if (key == ??) {

    }
    printf("x=%d y=%d\n", tmp->x, tmp->y);
}
char     start_line(t_edit **line, int display, int offset)
{
    int     key;
    t_edit  *tmp;

    tmp = *line;
    if (tmp)
    {
        tmp->x = offset;
        display == OFF ? cursor_display(line, OFF) : 0;
        while (1)
        {
            ft_putstr_fd("$> ", 2);
            key = get_key();
        }
    }
}

int     main(int ac, char **av)
{
    int     key;
    t_edit  *edit;

    if (ac == 1 && av)
    {
        if (!(edit = init_cmd_line()))
            return (0);
        if (init_term(&edit, 1))
        {
            ft_putendl("SUCCESS");
            ft_putstr_fd("$> ", 2);
            while (1)
            {
                key = get_key();
                write(1, &key, 1);
            }
        }
    }
}