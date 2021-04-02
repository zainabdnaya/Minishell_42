/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_pars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:20:01 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 17:37:43 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			quote_nbr(char *line, t_use *use)
{
	while (line[use->i] != '\0')
	{
		if (line[use->i] == '\\' && line[use->i + 1] != '\n')
		{
			norm_1(line, use);
			if (use->u % 2 != 0)
			{
				if (line[use->i++] == '\n')
					return (ret_norm_1());
				use->i++;
			}
			else if (use->u % 2 == 0)
				continue;
		}
		else if (line[use->i] == '\"' || line[use->i] == '\'')
		{
			if ((use->i = ret_norm_2(line, use)) == -1)
				break ;
		}
		else
			use->i++;
	}
	return (norm_ret_3(use));
}

void		check_line_error(char *line, t_shell *sh)
{
	t_use use;

	ft_bzero(&use, sizeof(t_use));
	if (quote_nbr(line, &use) == 1 || first_check(line) == 1 ||
			second_check(line) == 1)
	{
		sh->error = 1;
	}
	if (sh->error == 0 && search(line) == 1)
	{
		if (check_0(line) == 1 || check_1(line) == 1 ||
				first_check_1(line) == 1)
			sh->error = 1;
	}
}

int			norm_check1(char *line, int *i)
{
	(*i)++;
	while ((line[*i] == ' ' || line[*i] == '\t') && line[*i])
		(*i)++;
	if (line[*i] == '<')
		return (-1);
	else if (line[*i] == '>')
		return (-1);
	else if (line[*i] == ' ')
	{
		while (line[*i] == ' ')
			(*i)++;
		if (line[*i] == '<')
			return (-1);
	}
	return (*i);
}

void		norm_1(char *line, t_use *use)
{
	use->u = 0;
	while (line[use->i] == '\\')
	{
		use->u++;
		use->i++;
	}
}

int			norm_ret_3(t_use *use)
{
	if (use->j % 2 != 0 || use->k % 2 != 0)
		return (ret_norm_1());
	return (0);
}
