/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:15:36 by zjamali           #+#    #+#             */
/*   Updated: 2021/03/04 11:02:06 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		print_working_directory(t_path *path)
{
	char			*pwd;
	static char		*tmp;

	pwd = search_env(path->env->fullenv, "PWD");
	if (tmp && !pwd && !getcwd(pwd, 100))
		ft_putendl_fd(tmp, 1);
	if (!getcwd(pwd, 100))
		ft_putendl_fd(pwd, 1);
	else
	{
		ft_putendl_fd(getcwd(pwd, 100), 1);
		tmp = getcwd(pwd, 100);
	}
}
