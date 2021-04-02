/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:06:50 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/08 15:56:03 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		if_exit_red(t_all *all, t_path *path)
{
	path->index = 0;
	path->i = 0;
	if (ft_strcmp(all->command, "exit") == 0)
	{
		ft_putendl_fd(all->command, 1);
		if (!ft_strncmp(">>", all->red->sign, 2))
			path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
					O_APPEND, 0777);
		else if (!ft_strncmp(all->red->sign, ">", 1))
			path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
					O_TRUNC, 0777);
		exit(0);
	}
}

void		shift_now(t_all *all)
{
	int					fds[2];

	if (!ft_strcmp(all->red->sign, ">"))
	{
		if ((fds[1] = open(all->red->file_name, O_WRONLY | O_CREAT |
					O_TRUNC, 0777)) < 0)
			ft_putendl_fd(strerror(errno), 2);
		dup2(fds[1], 1);
		close(fds[1]);
	}
	if (!ft_strcmp(all->red->sign, ">>"))
	{
		if ((fds[1] = open(all->red->file_name, O_WRONLY | O_CREAT |
					O_APPEND, 0777)) < 0)
			ft_putendl_fd(strerror(errno), 2);
		dup2(fds[1], 1);
		close(fds[1]);
	}
}
