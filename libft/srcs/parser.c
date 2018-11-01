/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:15:44 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/28 09:21:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int		check_end(char *line)
{
	int		i;

	i = 0;
	while (line[i] && (is_space(line[i]) == 1 || line[i] == '\\'))
	{
		if (line[i] == '\\' && line[i + 1])
			break ;
		i++;
	}
	if (!line[i])
		return (0);
	return (1);
}

void    save_token(t_token **token, char **stack, int enable)
{
    (*token)->str = ft_strdup(*stack);
    (*token)->type = 0;
    ft_memset(*stack, '\0', ft_strlen(*stack));
    if (enable)
        free(*stack);
}

void    init_token(t_token **tok)
{
    if (!((*tok) = (t_token*)malloc(sizeof(t_token))))
        exit(0);
    (*tok)->str = NULL;
    (*tok)->type = 0;
    (*tok)->next = NULL;
}

t_token    *parser(char *str)
{
    int     i;
    int     j;
    char    *stack;
    t_token *start;
    t_token *tmp;

    i = 0;
    j = 0;
    
    init_token(&start);
    tmp = start;
    stack = ft_memalloc(100); // to dynamic allocation
    while (str[i])
    {
        if (str[i] != ' ')
        {
            stack[j++] = str[i];

        } else if (ft_strlen(stack) > 0){
            save_token(&tmp, &stack, 0);
            if (check_end(str + i))
            {
                init_token(&(tmp)->next);
                tmp = tmp->next;
            }
            j = 0;
        }
        i++;
    }
    if (ft_strlen(stack) > 0)
        save_token(&tmp, &stack, 1);
    return (start);
}