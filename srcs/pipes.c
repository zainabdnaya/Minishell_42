/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:28:49 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/07 11:06:17 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			lstsize(t_list_cmd *lst)
{
	t_pipe			*list1;
	t_all			*all;
	int				i;

	i = 0;
	list1 = lst->pipe;
	while (lst->pipe != NULL)
	{
		all = lst->pipe->all;
		while (lst->pipe->all != NULL)
		{
			i++;
			lst->pipe->all = lst->pipe->all->next;
		}
		lst->pipe->all = all;
		lst->pipe = lst->pipe->next;
	}
	lst->pipe = list1;
	return (i);
}

void		exe_with_re(t_shell *sh, t_list_cmd *lst, t_path *path)
{
	char			*cmd;

	if (lst->pipe->all->argument)
		cmd = ft_str_join(lst->pipe->all->command, " ",
				lst->pipe->all->argument);
	else if (!lst->pipe->all->argument)
		cmd = lst->pipe->all->command;
	if (search(lst->pipe->str_pipe) && lst->pipe->all->red->file_name)
		shift_extra(path, lst->pipe->all, sh);
	else if (search(lst->pipe->str_pipe) && !lst->all->red->file_name)
		shift_extra(path, lst->pipe->all, sh);
	else
		ft_execute1(lst->pipe->all, path);
	exit(0);
}

int			pipe_now(t_all *all, t_shell *sh, t_path *path, t_list_cmd *lst)
{
	int			fd[2];
	int			fd1[2];
	t_all		*all1;

	all1 = all;
	while (all)
	{
		pipe(fd);
		if ((path->pid = fork()) == -1)
			ft_error_free();
		else if (path->pid == 0)
		{
			check_fd(fd, fd1, path->i, path);
			exe_with_re(sh, lst, path);
		}
		else
		{
			ft_fd(fd, fd1);
			all = all->next;
		}
		path->i++;
	}
	all = all1;
	return (path->i);
}

void		pipes_cmd(t_path *path, t_list_cmd *lst, t_shell *sh)
{
	t_pipe		*tmp1;
	t_all		*all;

	path->size = lstsize(lst);
	tmp1 = lst->pipe;
	path->i = 0;
	while (lst->pipe)
	{
		all = lst->pipe->all;
		path->i = pipe_now(lst->pipe->all, sh, path, lst);
		lst->pipe->all = all;
		lst->pipe = lst->pipe->next;
	}
	lst->pipe = tmp1;
	while (0 < path->i--)
		wait(0);
}
