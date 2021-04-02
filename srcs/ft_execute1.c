/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:37:04 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/08 11:53:20 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_alpha(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '/' && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

void		ft_builtin2(t_all *all, t_path *path)
{
	if (ft_strcmp(all->command, "exit") == 0)
		ft_exit(all);
	else if (ft_strcmp(all->command, "$?") == 0)
	{
		path->dol_sign = 127;
		ft_putstr_fd("bash: ", 1);
		ft_putnbr_fd(path->dol_sign, 1);
		ft_putendl_fd(": Command not found", 1);
	}
	else
	{
		if (all->argument)
		{
			all->command = ft_strjoin(all->command, " ");
			all->command = ft_strjoin(all->command, all->argument);
		}
		if (all->command)
			exeute(path, all->command);
	}
}

void		ft_builtin1(t_all *all, t_path *path)
{
	if (ft_strcmp(all->command, "pwd") == 0)
		print_working_directory(path);
	else if (ft_strcmp(all->command, "unset") == 0)
		unset_cmd(all->argument, path);
	else if (ft_strcmp(all->command, "env") == 0)
		show_env(path->env->fullenv);
	else if (ft_strcmp(all->command, "export") == 0)
		export_cmd(all->argument, path);
	else if (ft_strcmp(all->command, "cd") == 0)
		cd_cmd(all->argument, path);
	else if (ft_strcmp(all->command, "echo") == 0)
	{
		if (all->argument)
			ft_echo(all->argument, 1, path);
		else
			ft_putstr_fd("\n", 1);
	}
	else if (ft_strcmp(all->command, "echo -n") == 0)
		ft_echo(all->argument, 0, path);
	else
		ft_builtin2(all, path);
}

void		put_err(t_all *all, t_path *path)
{
	path->dol_sign = 127;
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(all->command, 1);
	ft_putendl_fd(": Command not found", 1);
}

void		ft_execute1(t_all *all, t_path *path)
{
	int			len;
	char		**tmp;
	char		*tmp1;

	len = 0;
	tmp1 = all->command;
	all->command = replace_01(all->command, path);
	ft_stringdel(&tmp1);
	tmp1 = all->command;
	all->command = slach(all->command);
	ft_stringdel(&tmp1);
	tmp1 = all->command;
	all->command = no_quote(all->command);
	ft_stringdel(&tmp1);
	if (!((tmp = shell_space_split(all->command))))
		return ;
	if (count_line(tmp) == 1 && is_alpha(all->command))
		ft_builtin1(all, path);
	else if (count_line(tmp) > 1 || !is_alpha(all->command))
		put_err(all, path);
	ft_free_2dem_arr((void ***)&tmp);
}
