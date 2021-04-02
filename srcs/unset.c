/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 08:49:25 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/05 15:18:36 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**remove_env(t_path *path, char **args, int i)
{
	char		**env__p;
	int			j;
	int			k;
	char		**spl;

	j = 0;
	k = 0;
	path->check = 0;
	env__p = malloc(sizeof(char *) * count_line(path->env->fullenv));
	while (j < count_line(path->env->fullenv))
	{
		spl = ft_split(path->env->fullenv[j], '=');
		if (ft_strcmp(spl[0], "_"))
		{
			if (ft_strcmp(spl[0], args[i]))
				env__p[k++] = ft_strdup(path->env->fullenv[j]);
		}
		j++;
		ft_free_2dem_arr((void ***)&spl);
	}
	env__p[k] = NULL;
	return (env__p);
}

void		unset_cmd(char *name, t_path *path)
{
	int			i;
	char		**args;
	char		**env__p;

	i = -1;
	args = shell_space_split(name);
	while (args[++i])
	{
		env__p = remove_env(path, args, i);
		ft_free_2dem_arr((void ***)&path->env->fullenv);
		path->env->fullenv = env__p;
	}
	ft_free_2dem_arr((void ***)&args);
}
