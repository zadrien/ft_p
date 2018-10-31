/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 14:51:41 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 11:27:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int		ft_count_word(char *str, char c)
{
	int		i;
	int		w;

	i = 0;
	w = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			w++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (w);
}

static int		ft_count_letter(char *str, int i, char c)
{
	int		l;

	l = 0;
	while (str[i] != c && str[i] != '\0')
	{
		l++;
		i++;
	}
	return (l);
}

static void		ft_put_word(char **array, char *str, int l, char c)
{
	int		i;
	char	*word;

	i = 0;
	word = (char*)malloc(sizeof(char) * (l + 1));
	while (str[i] != c && str[i] != '\0')
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	*array = word;
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		l;
	int		tc;
	char	**t;

	tc = -1;
	i = ft_count_word((char *)s, c);
	if (!s || (!(t = (char**)malloc(sizeof(char*) * (i + 1)))))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			l = ft_count_letter((char *)s, i, c);
			ft_put_word(&t[++tc], (char *)s + i, l, c);
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	t[++tc] = 0;
	return (t);
}
