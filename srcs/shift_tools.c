/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:24:15 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/08 17:34:03 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			lstsize_2(t_redirection *red)
{
	t_redirection		*list1;
	int					i;

	i = 0;
	list1 = red;
	while (red != NULL)
	{
		i++;
		red = red->next;
	}
	red = list1;
	return (i);
}

int			ch_red_dif(t_list_cmd *lst, t_shell *sh)
{
	sh->red = 0;
	if (ft_strchr(lst->cmd, '>') && ft_strchr(lst->cmd, '<'))
		sh->red = 1;
	return (sh->red);
}
