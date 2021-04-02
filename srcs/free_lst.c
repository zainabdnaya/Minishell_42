/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 08:59:45 by zainabdnaya       #+#    #+#             */
/*   Updated: 2021/03/08 15:54:08 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		free_red(t_redirection **red)
{
	if ((*red)->sign != NULL)
	{
		free((*red)->sign);
		(*red)->sign = NULL;
	}
	if ((*red)->file_name != NULL)
	{
		free((*red)->file_name);
		(*red)->file_name = NULL;
	}
	free(*red);
	*red = NULL;
}

void		free_pipe(t_pipe *pipe)
{
	if (pipe->str_pipe != NULL)
		free(pipe->str_pipe);
	if (pipe->all != NULL)
	{
		free_all_node(&pipe->all);
	}
	free(pipe);
	pipe = NULL;
}

void		loop_norm2(t_list_cmd *lst)
{
	t_pipe			*p;
	t_redirection	*red;

	while (lst->pipe)
	{
		p = lst->pipe->next;
		if (lst->pipe->all->red)
			while (lst->pipe->all->red)
			{
				red = lst->pipe->all->red->next;
				free_red(&lst->pipe->all->red);
				lst->pipe->all->red = red;
			}
		free_pipe(lst->pipe);
		lst->pipe = p;
	}
}

void		loop_norm3(t_list_cmd *lst)
{
	t_all			*all;
	t_redirection	*red;

	while (lst->all)
	{
		all = lst->all->next;
		if (lst->all->red)
			while (lst->all->red)
			{
				red = lst->all->red->next;
				free_red(&lst->all->red);
				lst->all->red = red;
			}
		free_all_node(&lst->all);
		lst->all = all;
	}
}

void		free_lst(t_list_cmd *lst)
{
	t_list_cmd	*tmp;
	t_pipe		*p;

	p = NULL;
	while (lst)
	{
		tmp = lst->next;
		if (lst->pipe)
			loop_norm2(lst);
		if (lst->all)
			loop_norm3(lst);
		ft_stringdel(&lst->cmd);
		free(lst);
		lst = tmp;
	}
	lst = NULL;
}
