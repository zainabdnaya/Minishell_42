/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:39:14 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:26:20 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd		*handle_norm(t_read *rd, t_list_cmd *lst)
{
	t_shell sh;

	ft_bzero(&sh, sizeof(t_shell));
	lst = NULL;
	if (check_one(rd->line) == 1)
	{
		sh.simple_cmd = ft_minishell_split(rd->line, '|');
		lst = simple_cmd(lst, sh.simple_cmd);
	}
	else if (check_one(rd->line) == 2)
	{
		sh.simple_cmd = ft_minishell_split(rd->line, ';');
		lst = simple_cmd(lst, sh.simple_cmd);
	}
	else if (check_one(rd->line) == 3)
	{
		sh.simple_cmd = ft_minishell_split(rd->line, ';');
		lst = simple_cmd(lst, sh.simple_cmd);
	}
	comand_details(lst);
	free_2d_char(&sh.simple_cmd, count_line(sh.simple_cmd));
	return (lst);
}

t_list_cmd		*handle_line(t_read *rd, t_list_cmd *lst)
{
	t_shell		sh;
	char		*tmp;

	ft_bzero(&sh, sizeof(t_shell));
	lst = NULL;
	tmp = rd->line;
	rd->line = ft_strtrim(rd->line, "\n");
	ft_stringdel(&tmp);
	if (check_one(rd->line) == 0)
	{
		lst = creat_node(rd->line);
		define_each(lst);
		return (lst);
	}
	else
		lst = handle_norm(rd, lst);
	return (lst);
}
