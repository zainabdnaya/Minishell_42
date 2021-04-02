/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:18:20 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/07 11:08:24 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			lstsize_1(t_list_cmd *lst)
{
	t_list_cmd		*list1;
	t_all			*all;
	int				i;

	i = 0;
	list1 = lst;
	while (lst != NULL)
	{
		all = lst->all;
		while (lst->all != NULL)
		{
			i++;
			lst->all = lst->all->next;
		}
		lst->all = all;
		lst = lst->next;
	}
	lst = list1;
	return (i);
}

void		exe_with_re1(t_shell *sh, t_list_cmd *lst, t_path *path)
{
	char			*cmd;

	if (lst->all->argument && lst->all->command)
		cmd = ft_str_join(lst->all->command, " ", lst->all->argument);
	else
		cmd = lst->all->command;
	if (search(lst->cmd) && lst->all->red->file_name)
		shift_extra(path, lst->all, sh);
	else if (search(lst->cmd) && !lst->all->red->file_name)
		shift_extra(path, lst->all, sh);
	else
		ft_execute1(lst->all, path);
	exit(0);
}

void		check_fd1(int fd[2], int fd1[2], int i, t_path *path)
{
	if (i == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
	}
	else if (i == path->size - 1)
	{
		close(fd1[1]);
		dup2(fd1[0], 0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd1[1]);
		dup2(fd1[0], 0);
	}
}

int			pipe_now1(t_shell *sh, t_path *path, t_list_cmd *lst)
{
	int			fd[2];
	int			fd1[2];

	while (lst->all)
	{
		pipe(fd);
		if ((path->pid = fork()) == -1)
			ft_error_free();
		else if (path->pid == 0)
		{
			check_fd1(fd, fd1, path->i, path);
			exe_with_re1(sh, lst, path);
		}
		else
		{
			ft_fd(fd, fd1);
			lst->all = lst->all->next;
		}
		path->i++;
	}
	return (path->i);
}

void		pipes_cmd1(t_path *path, t_list_cmd *lst, t_shell *sh)
{
	t_list_cmd		*list1;
	t_all			*all;

	list1 = lst;
	path->size = lstsize_1(lst);
	list1 = lst;
	path->i = 0;
	while (lst != NULL)
	{
		all = lst->all;
		path->i = pipe_now1(sh, path, lst);
		lst->all = all;
		lst = lst->next;
	}
	lst = list1;
	while (0 < path->i--)
		wait(0);
}
