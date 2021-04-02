/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:34:53 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:55:38 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			dbl_quote_norm(const char *line, int *i)
{
	int u;

	u = 0;
	while (line[*i] == '\\')
	{
		u++;
		(*i)++;
	}
	return (u);
}

int			dbl_quote(const char *line, int i)
{
	int j;

	j = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			j = dbl_quote_norm(line, &i);
			if (line[i] == '\"')
			{
				if (j % 2 != 0)
					i++;
				else
					return (i);
			}
		}
		if (line[i] == '\"')
			return (i);
		i++;
	}
	j = 0;
	return (j);
}

int			spl_quote(const char *line, int i)
{
	int j;

	j = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			j = i;
			break ;
		}
		i++;
	}
	return (j);
}

int			norm_ligne2(const char *s, int i)
{
	if (s[i] == '\"')
	{
		i = dbl_quote(s, i + 1);
		return (i);
	}
	if (s[i] == '\'')
	{
		i = spl_quote(s, i + 1);
		return (i);
	}
	else
		return (i);
}

int			norm_check_loop(char s)
{
	if (s && (s == '\'' || s == '\"' || s == '\\') && s != ' ' && s != '\t')
		return (1);
	else
		return (0);
}
