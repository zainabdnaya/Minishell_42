/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:40:52 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:30:39 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		search_norm(char *str, int i, int k, int w)
{
	if (str[i] == '\\')
	{
		while (str[i] == '\\')
		{
			k++;
			i++;
		}
		if (k % 2 == 0 && (str[i] == '>' || str[i] == '<'))
			return (-2);
		else if (k % 2 != 0 && (str[i] == '>' || str[i] == '<'))
		{
			w = 1;
			i++;
		}
		else if (k % 2 != 0)
			i++;
	}
	if (str[i] == '\'')
		i = spl_quote(str, i + 1);
	if (str[i] == '\"')
		i = dbl_quote(str, i + 1);
	if (w == 1)
		return (-1);
	return (i);
}

int		search(char *str)
{
	t_use use;

	ft_bzero(&use, sizeof(t_use));
	if (str[use.i] == '\'' && str[use.i])
		use.i = spl_quote(str, use.i + 1) + 1;
	if (str[use.i] == '\"')
		use.i = dbl_quote(str, use.i + 1) + 1;
	while (str[use.i] != '\0')
	{
		use.i = search_norm(str, use.i, use.k, use.w);
		if (use.i == -1)
			return (0);
		else if (use.i == -2)
			return (1);
		else if (str[use.i] &&
				(str[use.i + 1] != '\0' || str[use.i + 1] != '\n') &&
				(str[use.i] == '>' || str[use.i] == '<'
				|| (str[use.i] == '>' && str[use.i + 1] == '>')))
			return (1);
		else
			use.i++;
	}
	return (0);
}

int		check_redirection(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '>')
			j = 1;
		else if (line[i] == '<')
			j = 2;
		else if (line[i] == '>' && line[i + 1] == '>')
			j = 3;
		i++;
	}
	return (j);
}
