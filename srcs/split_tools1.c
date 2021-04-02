/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:05:02 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:57:42 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			count_antislach(char *line, int i)
{
	int			j;
	int			result;

	j = 0;
	if (i < 0)
		return (1);
	while (line[i] == '\\' && i >= 0)
	{
		i--;
		j++;
	}
	result = j % 2;
	if (result == 0)
		return (1);
	else
		return (0);
}

void		*leak(char **spl, int j)
{
	j = j - 1;
	while (spl[j])
	{
		free(spl[j]);
		j--;
	}
	free(spl);
	return (NULL);
}

int			split_tool_norm(char *str, int i, char c_q)
{
	if (str[i] && (((str[i] == c_q && count_antislach(str, i - 1) == 0)
					|| str[i] != c_q)))
		return (1);
	return (0);
}

int			split_tool(char *str, int i, char c_q, int index)
{
	if (index == 1)
	{
		if (((str[i] == ' ' || str[i] == '\t') &&
					count_antislach(str, i - 1)) &&
				str[i])
			return (1);
	}
	else if (index == 2)
	{
		if (str[i] && (((str[i] == ' ' || str[i] == '\t') &&
						count_antislach(str, i - 1) == 0) ||
					(str[i] != ' ' && str[i] != '\t')))
			return (1);
	}
	else if (index == 3)
	{
		if (((c_q == 34 && str[i] == c_q &&
						count_antislach(str, i - 1) == 0) ||
					str[i] != c_q) &&
				str[i])
			return (1);
	}
	else if (index == 4)
		return (split_tool_norm(str, i, c_q));
	return (0);
}

int			norm_ligne3(const char *s, int i, int u)
{
	if ((s[i] == '\"' && s[i - 1] != '\\') || (s[i] == '\"' &&
				s[i - 1] == '\\' && u % 2 == 0))
	{
		i = dbl_quote(s, i + 1);
		return (i);
	}
	if ((s[i] == '\'' && s[i - 1] != '\\') || (s[i] == '\'' &&
				s[i - 1] == '\\' && u % 2 == 0))
	{
		i = spl_quote(s, i + 1);
		return (i);
	}
	else
		return (i);
}
