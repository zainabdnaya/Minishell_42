/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:28:12 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/08 15:56:19 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		check_dup(t_path *path, t_all *all, int index)
{
	if (index == 1)
	{
		if (dup2(path->file_desc, 1) < 0)
		{
			ft_putendl_fd(strerror(errno), 1);
			exit(EXIT_FAILURE);
		}
		close(path->file_desc);
		ft_execute1(all, path);
	}
	else if (index == 2)
	{
		if (dup2(path->file_desc, 0) < 0)
		{
			ft_putendl_fd(strerror(errno), 1);
			exit(EXIT_FAILURE);
		}
		close(path->file_desc);
		ft_execute1(all, path);
	}
}

int			che_red_type(t_path *path, t_all *all, int index)
{
	if (!ft_strcmp(">>", all->red->sign))
	{
		path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
				O_APPEND, 0777);
		index = 1;
	}
	else if (!ft_strcmp(all->red->sign, ">"))
	{
		path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
				O_TRUNC, 0777);
		index = 1;
	}
	else if (!ft_strcmp(all->red->sign, "<"))
	{
		if ((path->file_desc = open(all->red->file_name, O_RDONLY)) < 0)
			ft_putendl_fd(strerror(errno), 2);
		else
			index = 2;
	}
	return (index);
}

void		get_multi_red(t_path *path, t_all *all)
{
	t_redirection		*tmp1;
	int					fds[2];

	tmp1 = all->red;
	while (all->red)
	{
		shift_now(all);
		if (!ft_strcmp(all->red->sign, "<"))
		{
			if ((fds[0] = open(all->red->file_name, O_RDONLY)) < 0)
			{
				path->check_shift = 1;
				ft_putendl_fd(strerror(errno), 2);
				break ;
			}
			dup2(fds[0], 0);
			close(fds[0]);
		}
		all->red = all->red->next;
	}
	all->red = tmp1;
}

void		get_multi_red2(t_all *all, t_path *path)
{
	path->size = lstsize_2(all->red);
	while (path->size != 1 && path->i < path->size - 1)
	{
		if (ft_strcmp(all->red->sign, ">") || ft_strcmp(all->red->sign, " >>"))
			path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
					O_APPEND, 0777);
		all->red = all->red->next;
		path->i++;
	}
}

void		shift_extra(t_path *path, t_all *all, t_shell *sh)
{
	(void)sh;
	if_exit_red(all, path);
	if ((path->pid = fork()) == 0)
	{
		path->check_shift = 0;
		get_multi_red(path, all);
		if (!path->check_shift)
			ft_execute1(all, path);
		exit(0);
	}
	wait(0);
}
