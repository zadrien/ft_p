/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 08:32:58 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 08:33:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    print_msg(char *str, char *color, int fd)
{
    ft_putstr_fd(color, fd);
    ft_putendl_fd(str, fd);
    ft_putstr_fd(RESET, fd);
}