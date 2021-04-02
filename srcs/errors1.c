/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:49:20 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:46:18 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		norm_check2(char *line, int *i)
{
	(*i)++;
	while ((line[(*i)] == ' ' || line[(*i)] == '\t') && line[(*i)])
		(*i)++;
	if (line[(*i)] == '>' || line[(*i)] == '<')
		return (-1);
	else if (line[(*i)] == ' ')
	{
		while (line[(*i)] == ' ')
			(*i)++;
		if (line[(*i)] == '>' || line[*i] == '<')
			return (-1);
	}
	return (*i);
}

int		check_1(char *line)
{
	int i;

	i = 0;
	while (line[i++])
	{
		if (line[i] == '>' && line[i + 1] != '>')
		{
			if ((i = norm_check1(line, &i)) == -1)
				return (ret_norm_1());
		}
		else if (line[i] == '<')
		{
			if ((i = norm_check2(line, &i)) == -1)
				return (ret_norm_1());
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			i = i + 2;
			while ((line[i] == ' ' || line[i] == '\t') && line[i])
				i++;
			if (line[i] == '>' || line[i] == '<')
				return (ret_norm_1());
		}
	}
	return (0);
}

int		ret_norm_1(void)
{
	write(1, "Error:Syntax error\n", 20);
	return (1);
}

int		ret_norm_2(char *line, t_use *use)
{
	if (line[use->i] == '\"')
	{
		use->j++;
		use->i = dbl_quote(line, use->i + 1) + 1;
		if (use->i > 1)
			use->j++;
		else
			return (-1);
	}
	else if (line[use->i] == '\'')
	{
		use->k++;
		use->i = spl_quote(line, use->i + 1) + 1;
		if (use->i > 1)
			use->k++;
		else
			return (-1);
	}
	return (use->i);
}

void	norm_inc(t_use *use)
{
	use->u++;
	use->i++;
}
