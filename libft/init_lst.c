/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 16:35:38 by zadrien           #+#    #+#             */
/*   Updated: 2017/04/18 16:40:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
****************************************************************************
**            Function type to change in term of your struct             **
**************************************************************************
*/

t_tok	init_lst(t_tok **lst)
{
	if (!((*lst = (t_tok*)malloc(sizeof(t_tok)))))
		return (NULL);
	return ((*lst));
}