/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:32:42 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:49:08 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		norm_loop(int *i, char *line)
{
	(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

void		norm_loop_2(int *i, char *line)
{
	*i = *i + 2;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

int			first_check_1(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '<' && line[i + 1] == '<') ||
				(line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<'))
			return (ret_norm_1());
		else if ((line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>'))
			return (ret_norm_1());
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			norm_loop_2(&i, line);
			if (line[i] == '\n' || line[i] == '\0')
				return (ret_norm_1());
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			norm_loop(&i, line);
			if (line[i] == '\n' || line[i] == '\0')
				return (ret_norm_1());
		}
		i++;
	}
	return (0);
}

int			first_check(char *line)
{
	int i;

	i = 0;
	if (line[0] == '|' || line[0] == ';')
		return (ret_norm_1());
	else if ((line[0] == '\'' || line[0] == '\"')
			&& ((line[1] == '<' || line[1] == '>' ||
					(line[1] == '>' && line[2] == '>'))))
		return (ret_norm_1());
	else
	{
		while ((line[i] == ' ' || line[i] == '\t') && line[i])
			i++;
		if (line[i] == '|')
			return (ret_norm_1());
		else if (line[i] == ';')
			return (ret_norm_1());
		else if (line[i] == '\\' && line[i + 1] == '\n')
			return (ret_norm_1());
		else if (line[i] == '$' && line[i + 1] == '\\' && line[i + 2] == '\n')
			return (ret_norm_1());
		else
			return (0);
	}
}

int			second_check(char *line)
{
	int i;

	i = 0;
	while (line[i] != ';' && line[i] != '|' && line[i] != '\"'
			&& line[i] != '\''
			&& line[i] && line[i] != '\\')
		i++;
	if (line[i] == '\"')
		i = dbl_quote(line, i + 1) + 1;
	if (line[i] == '\'')
		i = spl_quote(line, i + 1) + 1;
	if ((line[i] == ';' || line[i] == '|') && line[i])
	{
		i++;
		while ((line[i] == ' ' || line[i] == '\t') && line[i])
			i++;
		if (line[i] == ';' || line[i] == '|')
			return (ret_norm_1());
	}
	return (0);
}
