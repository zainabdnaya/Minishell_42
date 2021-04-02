/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lanch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:06:18 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:22:23 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*last_norm(char **line, t_use *use, char *tmp, char *tmp2)
{
	if ((norm_red(line[use->i]) == 1 || norm_red(line[use->i]) == 2))
		tmp = after_norm(line, tmp, tmp2, use);
	else if (check_redirection(line[use->i]) != 0)
		tmp = after_norm1(line, tmp, use);
	else if (use->i >= 1 && kayna2(tmp) == 1 && condition_2(line, use->i) == 0)
	{
		tmp = replace(tmp, line[use->i]);
		use->i++;
	}
	free(tmp2);
	tmp2 = NULL;
	return (tmp);
}

char		*is_after_redirection(char *s)
{
	char		*tmp;
	t_use		use;
	char		*tmp2;
	char		**line;

	tmp2 = NULL;
	tmp = NULL;
	line = shell_space_split(s);
	ft_bzero(&use, sizeof(t_use));
	tmp = malloc(sizeof(char) * (ft_strlen(s)));
	ft_bzero(tmp, sizeof(char) * (ft_strlen(s)));
	while (line[use.i])
	{
		if (condition_if(line, use) == 1)
			tmp = norm_first(line, &use, tmp);
		else
			tmp = last_norm(line, &use, tmp, tmp2);
	}
	free_2d_char(&(line), count_line(line));
	return (tmp);
}

t_all		*s_cmd_details(char *s1, char *s2, char *s3)
{
	t_all *all;

	all = malloc(sizeof(t_all));
	all->command = s1;
	all->argument = s2;
	all->redirection = s3;
	all->red = NULL;
	all->next = NULL;
	return (all);
}

char		witch_quote(char *s, int i)
{
	int k;

	while (s[i++])
	{
		if (s[i] == '\\')
		{
			k = 0;
			while (s[i] == '\\')
			{
				k++;
				i++;
			}
			if (k % 2 == 0 && (s[i] == 39))
				return ('\'');
			else if (k % 2 == 0 && (s[i] == 34))
				return ('\"');
			else
				i++;
		}
		if (s[i] == 39)
			return ('\'');
		if (s[i] == 34)
			return ('\"');
	}
	return ('\0');
}

int			we_have_quote(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
