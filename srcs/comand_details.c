/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_details.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:25 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:31:58 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		comand_details(t_list_cmd *lst)
{
	t_list_cmd *lstt;

	lst = link_list(lst);
	lstt = lst;
	while (lst != NULL)
	{
		if (pipe_e(lst->cmd) == 1)
			part_one(lst);
		else
		{
			if (pipe_e(lst->cmd) == 1)
				lst = lst->next;
			else
				part_two(lst);
		}
		lst = lst->next;
	}
	lst = lstt;
}

void		part_two(t_list_cmd *lst)
{
	char *string;
	char *red;

	if (search(lst->cmd) == 1)
	{
		string = is_befor_redirection(lst->cmd);
		red = is_after_redirection(lst->cmd);
		lst = parsing_red(lst, string, red);
		ft_stringdel(&string);
		ft_stringdel(&red);
	}
	else
		lst = spl_cmd(lst);
}

void		part_one(t_list_cmd *lst)
{
	t_pipe		*pipe;
	char		*string;
	char		*red;

	pipe = lst->pipe;
	while (lst->pipe != NULL)
	{
		if (search(lst->pipe->str_pipe) == 1)
		{
			string = is_befor_redirection(lst->pipe->str_pipe);
			red = is_after_redirection(lst->pipe->str_pipe);
			lst = pars_p_r(lst, string, red);
			ft_stringdel(&string);
			ft_stringdel(&red);
		}
		else
			lst = pars_pipe(lst);
		lst->pipe = lst->pipe->next;
	}
	lst->pipe = pipe;
}

int			ft_strlen_to_char(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '>' && str[i] != '<')
	{
		if (str[i] == '\\' || str[i] == '\'' || str[i] == '\"')
			i = index_1(str, i);
		i++;
	}
	return (i);
}

t_list_cmd	*sort_all_2(t_list_cmd *lst, t_all *all, char **free_sp)
{
	t_use use;

	ft_bzero(&use, sizeof(t_use));
	while (free_sp[use.i] != NULL)
	{
		if (condition_1(free_sp, use.i) == 1 ||
				condition_2(free_sp, use.i) == 1)
			all = all_conditions(all, free_sp, &use.i);
		else
			condition_3(&use, &free_sp);
	}
	lst->all = update_all(lst->all, use.cmd2, use.arg1, all->red);
	return (lst);
}
