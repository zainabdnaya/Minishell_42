/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 13:38:56 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/07 11:40:37 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			index_of_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int			check_equal_1(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int			check_equal(char *env)
{
	int		i;

	i = 0;
	while (env[i] && i != (int)ft_strlen(env))
	{
		if (env[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void		show_env(char **env)
{
	int		i;
	int		c;

	if (!env)
		return ;
	c = '\n';
	i = 0;
	while (env[i] && (check_equal(env[i]) == 1))
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, &c, 1);
		i++;
	}
}

void		sort1(char **env, char **spl, int i, int index)
{
	int		j;
	int		c;

	c = '\n';
	j = 0;
	if (ft_strcmp(spl[0], "_"))
	{
		write(1, "declare -x ", 11);
		if (check_equal_1(env[i]))
			index = index_of_equal(env[i]);
		j = 0;
		while (env[i][j])
		{
			write(1, &env[i][j], 1);
			if (j == index)
				write(1, "\"", 1);
			j++;
		}
		if (check_equal_1(env[i]))
			write(1, "\"", 1);
		c = '\n';
		write(1, &c, 1);
	}
}
