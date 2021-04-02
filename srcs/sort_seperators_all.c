/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_seperators_all.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:47:27 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:52:11 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd		*pars_p_r(t_list_cmd *lst, char *string, char *red)
{
	t_all		*new1;
	char		**tmp;
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
	new1 = s_cmd_details(use.cmd, use.arg, red);
	add_all(&lst->pipe->all, new1);
	lst = pars_red(lst, red, &use);
	if (tmp)
		free_2d_char(&(tmp), count_line(tmp));
	ft_stringdel(&(use.arg));
	ft_stringdel(&(use.cmd));
	return (lst);
}

t_list_cmd		*pars_pipe(t_list_cmd *lst)
{
	char		**red;
	char		*cmd;
	char		*arg;
	t_all		*new1;
	char		*string;

	string = ft_strdup(lst->pipe->str_pipe);
	red = shell_space_split(string);
	cmd = red[0];
	arg = concat(red, 1);
	new1 = s_cmd_details1(cmd, arg);
	add_all(&lst->pipe->all, new1);
	if (red)
		free_2d_char(&(red), count_line(red));
	ft_stringdel(&string);
	ft_stringdel(&arg);
	return (lst);
}
