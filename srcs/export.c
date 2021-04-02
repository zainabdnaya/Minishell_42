/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 10:58:45 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/08 15:34:37 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				sort_exp(char **env, int i, int k)
{
	char			**ret;
	char			*tmp;

	i = -1;
	k = 0;
	ret = malloc((count_line(env) + 1) * sizeof(char *));
	while (++i < count_line(env))
		ret[i] = env[i];
	i = -1;
	while (++i < count_line(env))
	{
		k = i + 1;
		while (k < count_line(env))
		{
			if (ft_strcmp(ret[i], ret[k]) > 0)
			{
				tmp = ret[i];
				ret[i] = ret[k];
				ret[k] = tmp;
			}
			k++;
		}
	}
	ret[i] = NULL;
	show_env1(ret);
}

char				**add_export(char **env__p, t_path *path, int *j, char *ar)
{
	char *tmp;

	while (path->env->fullenv[*j])
	{
		tmp = env__p[*j];
		env__p[*j] = ft_strdup(path->env->fullenv[*j]);
		(*j)++;
	}
	env__p[(*j)++] = ft_strdup(ar);
	env__p[*j] = NULL;
	return (env__p);
}

void				export_now(t_path *path, char *args)
{
	int				che_mod;
	char			**env__p;
	int				j;
	int				len;

	len = count_line(path->env->fullenv);
	env__p = (char **)malloc(sizeof(char *) * (len + 2));
	j = 0;
	che_mod = -1;
	if ((che_mod = is_modif(args, che_mod, path)) < 0)
		env__p = add_export(env__p, path, &j, args);
	else
	{
		while (path->env->fullenv[j])
		{
			if ((j == che_mod) && ft_strchr(args, '='))
				env__p[j] = ft_strdup(args);
			else
				env__p[j] = ft_strdup(path->env->fullenv[j]);
			j++;
		}
		env__p[j] = NULL;
	}
	ft_free_2dem_arr((void ***)&path->env->fullenv);
	path->env->fullenv = env__p;
}

void				export_cmd(char *n, t_path *path)
{
	char			**args;
	int				i;
	int				j;

	j = -1;
	i = -1;
	if (!n)
		return ((void)sort_exp(path->env->fullenv, i, j));
	args = shell_space_split(n);
	i = 0;
	while (args[i])
	{
		args[i] = no_quote(slach(args[i]));
		if (checkis_valid_var(args[i]))
			export_now(path, args[i]);
		else
		{
			path->dol_sign = 1;
			ft_putendl_fd("not a valid identifer", 2);
		}
		i++;
	}
	ft_free_2dem_arr((void ***)&args);
}
