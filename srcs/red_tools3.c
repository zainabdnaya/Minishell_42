/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:40:47 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:49:43 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			count_slach(char *line)
{
	int i;

	i = 0;
	while (line[i] == '\\')
		i++;
	return (i);
}

void		norm_inct(int *k, int *i)
{
	(*k)++;
	(*i)++;
}

int			count(char *s)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == '\\')
		{
			k = 0;
			while (s[i] == '\\')
				norm_inct(&k, &i);
			if (s[i] == '>' || s[i] == '<')
			{
				if (k % 2 != 0)
					return (1);
				return (0);
			}
		}
		if (s[i] == '\"' || s[i] == '\'')
			i = (s[i] == '\"') ? dbl_quote(s, i + 1) : spl_quote(s, i + 1);
		i++;
	}
	return (0);
}

int			kayna2(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	if ((str[i - 1] == '>' || str[i - 1] == '<') && count(str) == 0)
		return (1);
	return (0);
}

char		*replace(char *tmp, char *s2)
{
	char *s;

	if (!tmp && !s2)
		return (NULL);
	if (tmp == NULL)
		return (ft_strdup(s2));
	else
	{
		s = tmp;
		tmp = concat_space(s2, tmp);
		ft_stringdel(&s);
	}
	return (tmp);
}
