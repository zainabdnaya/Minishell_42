/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:47:52 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/27 18:07:38 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		check_fd(int fd[2], int fd1[2], int i, t_path *path)
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

void		ft_error_free(void)
{
	ft_putendl_fd("error in fork", 2);
	exit(1);
}

void		ft_fd(int fd[2], int fd1[2])
{
	close(fd1[0]);
	close(fd[1]);
	fd1[0] = fd[0];
	fd1[1] = fd[1];
}
