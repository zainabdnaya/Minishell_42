/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:44:55 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:47:30 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			kayna(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if ((str[i - 1] == '>' || str[i - 1] == '<')
			&& str[i - 1] != '\\' && str[i - 2] != '\\')
		return (1);
	return (0);
}

void		norm_reds(int *j, int *i, int *k, char *line)
{
	*j = 0;
	*i = 0;
	*k = 0;
	if ((line[*i] == '>' && line[(*i) + 1] == '>'))
		(*j)++;
	if ((line[*i] == '>' || line[*i] == '<'))
		(*j)++;
}

void		norn_red1(int k, int *i, int *j)
{
	if (k % 2 == 0)
		norm_inct(i, j);
	else
		(*i)++;
}

void		norm_red2(char *line, int *i, int *j)
{
	if ((line[*i] == '>' || line[*i] == '<') &&
			(line[*i - 1] != '\\' && *i >= 1))
		norm_inct(i, j);
	else
		(*i)++;
}

int			number_red(char *line)
{
	int j;
	int i;
	int k;

	norm_reds(&j, &i, &k, line);
	while (line[i])
	{
		if (line[i] == '\\')
		{
			k = 0;
			while (line[i] == '\\')
			{
				norm_inct(&i, &k);
			}
			norn_red1(k, &i, &j);
		}
		if ((line[i] == '>' && line[i + 1] == '>'))
		{
			i = i + 2;
			j++;
		}
		norm_red2(line, &i, &j);
	}
	return (j);
}
