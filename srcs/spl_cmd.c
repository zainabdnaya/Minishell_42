/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:15:47 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:53:20 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd		*define_each(t_list_cmd *lst)
{
	char		*string;
	char		*red;

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
	return (lst);
}

t_list_cmd		*spl_cmd(t_list_cmd *lst)
{
	char		*string;
	char		**free_sp;
	char		*cmd;
	char		*arg;
	t_all		*new1;

	string = ft_strdup(lst->cmd);
	free_sp = NULL;
	free_sp = shell_space_split(string);
	cmd = free_sp[0];
	arg = concat(free_sp, 1);
	new1 = s_cmd_details1(cmd, arg);
	add_all(&lst->all, new1);
	if (free_sp)
		free_2d_char(&(free_sp), count_line(free_sp));
	free(string);
	free(arg);
	return (lst);
}

void			norm_null1(t_use *use)
{
	use->arg = NULL;
	use->cmd = NULL;
}

t_list_cmd		*parsing_red(t_list_cmd *lst, char *string, char *red)
{
	char		**tmp;
	t_all		*tmp1;
	t_use		use;

	ft_bzero(&use, sizeof(t_use));
	tmp = NULL;
	(!string) ? norm_null1(&use) : NULL;
	if (string)
	{
		tmp = shell_space_split(string);
		use.cmd = ft_strdup(tmp[0]);
		use.arg = concat(tmp, 1);
	}
	tmp1 = s_cmd_details((use.cmd), (use.arg), red);
	add_all(&lst->all, tmp1);
	lst = redirection_sort(lst, &use, red);
	if (tmp)
		free_2d_char(&(tmp), count_line(tmp));
	free(use.arg);
	free(use.cmd);
	return (lst);
}
