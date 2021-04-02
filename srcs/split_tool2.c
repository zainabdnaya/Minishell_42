/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tool2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:08:52 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:54:39 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			norm_ligne(const char *s, int i)
{
	int			u;
	int			z;

	u = 0;
	z = 0;
	while (norm_check_loop(s[i]))
	{
		if (s[i] == '\\' && s[i])
		{
			u = dbl_quote_norm(s, &i);
			i = u + i;
			if (s[i] == ' ' || s[i] == '\t')
				z = 1;
			if (u % 2 != 0)
				i++;
			else if (u % 2 == 0 && z == 1)
				return (i);
			else
				i = norm_ligne3(s, i, u);
		}
		else
			i = norm_ligne2(s, i);
		i++;
	}
	return (i);
}

int			ligne(const char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		while (s[i] && s[i] != ' ' && s[i] != '\t' &&
				s[i] != '\"' && s[i] != '\'' && s[i] != '\\')
			i++;
		if (s[i] && (s[i] == '\'' || s[i] == '\"' || s[i] == '\\'))
			i = norm_ligne(s, i);
		while (s[i] && s[i] != ' ' && s[i] != '\t' &&
				s[i] != '\"' && s[i] != '\'' && s[i] != '\\')
			i++;
		while ((s[i] == ' ' || s[i] == '\t') && s[i])
			i++;
		j++;
	}
	return (j);
}

int			check_antislach(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			i = spl_quote(s, i + 1);
		else if (s[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

char		*slach(char *s)
{
	if (check_antislach(s) == 1)
		return (no_antislach(s));
	else
		return (ft_strdup(s));
}

int			count_slash(char *s, int i)
{
	int j;

	j = 0;
	while (s[i] == '\\' && s[i])
	{
		j++;
		i++;
	}
	return (j);
}
