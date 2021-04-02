/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:30:13 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 17:11:32 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		call_getprg_1(t_list_cmd *lst, t_path *path, t_shell *sh)
{
	t_list_cmd		*tmp;
	t_all			*tmp1;

	tmp = lst;
	tmp1 = lst->all;
	ch_red_dif(lst, sh);
	while (lst->all != NULL)
	{
		if (search(lst->cmd) && lst->all->red->file_name)
			shift_extra(path, lst->all, sh);
		else if (search(lst->cmd) && !lst->all->red->file_name)
			shift_extra(path, lst->all, sh);
		else
		{
			ft_execute1(lst->all, path);
		}
		lst->all = lst->all->next;
	}
	lst->all = tmp1;
}

void		call_getprg(t_list_cmd *lst, t_path *path, t_shell *sh)
{
	t_list_cmd		*tmp;

	tmp = lst;
	while (lst != NULL)
	{
		call_getprg_1(lst, path, sh);
		lst = lst->next;
	}
	lst = tmp;
}

void		call_pipe(t_list_cmd *lst, t_path *path, t_shell *sh)
{
	t_list_cmd		*list1;

	list1 = lst;
	while (lst != NULL)
	{
		if (pipe_e(lst->cmd) == 1)
			pipes_cmd(path, lst, sh);
		else
			call_getprg_1(lst, path, sh);
		lst = lst->next;
	}
	lst = list1;
}
