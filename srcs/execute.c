/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:04:15 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/07 11:51:22 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_var1 = 0;

void				exe(char *p1, char *cmd, char **tmp1, t_path *path)
{
	int				status;
	int				a;

	status = 0;
	a = fork();
	if (a < 0)
		exit(1);
	if (!a)
	{
		if (p1 && cmd[0] != '\n' && tmp1[0])
			if (execve(p1, tmp1, path->env->fullenv) == -1)
			{
				ft_putstr_fd("bash: ", 1);
				ft_putstr_fd(p1, 1);
				ft_putendl_fd(": commande not found", 1);
			}
		exit(0);
	}
	wait(&status);
	if (WEXITSTATUS(status))
		path->dol_sign = WEXITSTATUS(status);
	else
		path->dol_sign = 0;
}

char				*ft_get_cmd(char *p1, char *p, char **tmp1, t_path *path)
{
	if (is_slash(tmp1[0]) == 1)
	{
		p1 = ft_strdup(tmp1[0]);
		path->d = 1;
	}
	else if (path->i == 0 && !p)
	{
		p1 = getcwd(NULL, 100);
		p1 = ft_strjoin(p1, "/");
		p1 = ft_strjoin(p1, tmp1[0]);
		path->d = 1;
	}
	else if (!path->d && g_var1)
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(tmp1[0], 1);
		ft_putendl_fd(": commande not found", 1);
		path->dol_sign = 127;
	}
	return (p1);
}

char				*cmd_slash(char **tmp, char *p1, t_path *path, char **tmp1)
{
	struct stat		buffer;
	char			*tmp2;

	path->i = -1;
	while (tmp[++path->i])
	{
		tmp2 = tmp[path->i];
		tmp[path->i] = ft_strjoin(tmp[path->i], "/");
		ft_free_arr((void **)&tmp2);
		tmp2 = tmp[path->i];
		tmp[path->i] = ft_strjoin(tmp[path->i], tmp1[0]);
		ft_free_arr((void **)&tmp2);
		if (lstat(tmp[path->i], &buffer) == 0)
		{
			p1 = ft_strdup(tmp[path->i]);
			path->d = 1;
			break ;
		}
	}
	return (p1);
}

void				ft_puts_err(char **tmp1, t_path *path)
{
	g_var1 = 1;
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(tmp1[0], 1);
	ft_putendl_fd(": commande not found", 1);
	path->dol_sign = 127;
	ft_free_2dem_arr((void ***)&tmp1);
}

void				exeute(t_path *path, char *cmd)
{
	char			**tmp;
	char			**tmp1;
	char			*p;
	char			*p1;

	path->i = -1;
	p1 = NULL;
	tmp1 = shell_space_split(cmd);
	p = get_var_env(path, "$PATH");
	if (tmp1[0])
	{
		if (p)
		{
			tmp = ft_split(p, ':');
			p1 = cmd_slash(tmp, p1, path, tmp1);
			ft_free_2dem_arr((void ***)&tmp);
		}
		p1 = ft_get_cmd(p1, p, tmp1, path);
		if (!p1)
			return ((void)ft_puts_err(tmp1, path));
		if (path->d && !g_var1)
			exe(p1, cmd, tmp1, path);
	}
	ft_free_2dem_arr((void ***)&tmp1);
	ft_free_arr((void **)&p1);
}
