/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolars_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 10:26:10 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:34:36 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_isalpha2(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int		is_valid(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int		until_dollar(char *s, int i)
{
	if (s[i])
	{
		while (s[i])
		{
			if (s[i] == '\'')
				i = spl_quote(s, i + 1) + 1;
			else if (s[i] == '$' && s[i + 1] == '\\')
				i++;
			else if (s[i] == '\\' && s[i + 1] == '$')
				i++;
			else if (s[i] == '$' && s[i + 1] == '$')
				i++;
			else if (s[i] == '$' && s[i + 1] != '$')
				return (i);
			i++;
		}
	}
	return (i);
}

int		in_dollar(char *s, int i)
{
	int j;

	j = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i])
		{
			while ((s[i] == '$' || ft_isalpha2(s[i]) || ft_isdigit(s[i]))
					&& s[i])
			{
				j++;
				i++;
			}
			return (j);
		}
		i++;
	}
	return (j);
}

int		strlen_tmp(t_tmp *tmp)
{
	int i;

	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
