/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:57:14 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/07 10:42:50 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	quote_char(char *str, t_shell *sh)
{
	int		i;

	i = 0;
	sh->db_quote = 0;
	sh->sp_quote = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			sh->db_quote = 1;
			return ('\"');
		}
		else if (str[i] == 39)
		{
			sh->sp_quote = 1;
			return ('\'');
		}
		i++;
	}
	return (0);
}

int		escap_slach(char *line, int i, int u)
{
	int k;

	k = 0;
	u = 0;
	while (line[i] == '\\' && line[i])
	{
		u++;
		i++;
	}
	if (u % 2 != 0)
		k = i + 1;
	else if (u % 2 == 0)
		k = i;
	return (k);
}

void	ft_check_comma(char *line, t_shell *sh)
{
	int i;
	int u;

	i = 0;
	u = 0;
	while (line[i])
	{
		if (line[i] == '\\')
			i = escap_slach(line, i, u);
		else if (line[i] == '\"')
			i = dbl_quote(line, i + 1) + 1;
		else if (line[i] == '\'')
			i = spl_quote(line, i + 1) + 1;
		else
		{
			if (line[i] == ';')
			{
				sh->comma = 1;
				break ;
			}
			i++;
		}
	}
}

void	ft_check_pipe(char *line, t_shell *sh)
{
	int i;
	int u;

	i = 0;
	u = 0;
	while (line[i])
	{
		if (line[i] == '\\')
			i = escap_slach(line, i, u);
		else if (line[i] == '\"')
			i = dbl_quote(line, i + 1) + 1;
		else if (line[i] == '\'')
			i = spl_quote(line, i + 1) + 1;
		else
		{
			if (line[i] == '|')
			{
				sh->pipe = 1;
				break ;
			}
			i++;
		}
	}
}

int		check_one(char *line)
{
	t_shell sh;

	ft_bzero(&sh, sizeof(t_shell));
	if (line)
	{
		ft_check_comma(line, &sh);
		ft_check_pipe(line, &sh);
		if (sh.pipe == 1 && sh.comma == 0)
			return (1);
		else if (sh.pipe == 0 && sh.comma == 1)
			return (2);
		else if (sh.pipe == 1 && sh.comma == 1)
			return (3);
		else
			return (0);
	}
	return (-1);
}
