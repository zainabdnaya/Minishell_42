/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:40:31 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:48:37 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			search_2(char *str)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			while (str[i] == '\\')
			{
				i++;
				k++;
			}
			if (k % 2 == 0 && (str[i] == '>' || str[i] == '<'))
				return (1);
			else if (k % 2 != 0 && (str[i] == '>' || str[i] == '<'))
				i++;
		}
		if (str[i] == '>' || str[i] == '<' || str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int			count_from(char *line, int i)
{
	int j;

	j = 0;
	if (line[i] == '>' || line[i] == '<')
		while (line[i] != '\0')
			j++;
	return (j);
}

int			norm_red(char *line)
{
	int i;

	i = 0;
	if (line[i] == '\\')
		return (2);
	if (line[i] == '\"' || line[i] == '\'')
		return (1);
	if (line[i] == '>' || line[i] == '<')
		return (3);
	else
		return (0);
}
