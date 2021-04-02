/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 10:57:49 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/07 11:47:59 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*ft_str_in_str(const char *s1, const char *s2)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (!s2[j])
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			j = 1;
			while (s2[j] && s2[j] == s1[i + j])
				j++;
			if (!s2[j] && !s1[i + j])
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}

int				ft_2strlen(char **str)
{
	int			i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

int				count_line(char **env)
{
	int i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

void			show_env1(char **env)
{
	int		i;
	int		index;
	char	**spl;

	if (!env)
		return ;
	i = 0;
	index = 0;
	while (env[i])
	{
		spl = ft_split(env[i], '=');
		sort1(env, spl, i, index);
		ft_free_2dem_arr((void ***)&spl);
		i++;
	}
}

int				is_slash(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
