/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:05:19 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:05:35 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd		*creat_node(char *content)
{
	t_list_cmd *lst;

	lst = malloc(sizeof(t_list_cmd));
	lst->cmd = ft_strtrim(content, "\n");
	lst->pipe = NULL;
	lst->all = NULL;
	lst->next = NULL;
	return (lst);
}

t_redirection	*creat_node_r(char *content, char *content1)
{
	t_redirection *red;

	red = malloc(sizeof(t_redirection));
	red->sign = ft_strtrim(content, "\n");
	red->file_name = ft_strtrim(content1, "\n");
	red->next = NULL;
	return (red);
}

t_pipe			*creat_node_p(char *content)
{
	t_pipe *lst;

	lst = malloc(sizeof(t_pipe));
	lst->str_pipe = ft_strtrim(content, "\n");
	lst->all = NULL;
	lst->next = NULL;
	return (lst);
}

t_all			*update_all(t_all *new_all, char *cmd, char *arg,
		t_redirection *red)
{
	new_all->command = ft_strtrim(cmd, "\n");
	new_all->argument = ft_strtrim(arg, "\n");
	new_all->red = red;
	new_all->next = NULL;
	return (new_all);
}

t_tmp			*creat_tmp(char *s1)
{
	t_tmp *tmp;

	tmp = malloc(sizeof(t_tmp));
	tmp->s1 = ft_strdup(s1);
	tmp->next = NULL;
	return (tmp);
}
