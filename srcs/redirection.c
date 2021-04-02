/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:34:31 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:46:44 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*pars_red_norm1(char *red, t_use *use, char *tmp)
{
	int		k;
	int		j;

	k = 0;
	j = 0;
	while (red[use->i] != '\0' && red[use->i] != '>' && red[use->i] != '<' &&
			red[use->i] != '\t' && red[use->i] != ' ' && red[use->i] != '\n')
	{
		if (red[use->i] == '\\' || red[use->i] == '\'' || red[use->i] == '\"')
		{
			j = index_1(red, use->i);
			while (use->i < j)
				tmp[k++] = red[(use->i)++];
		}
		else
			tmp[k++] = red[(use->i)++];
	}
	tmp[k] = '\0';
	return (tmp);
}

t_list_cmd		*pars_red(t_list_cmd *lst, char *r, t_use *use)
{
	char *tmp;

	while (r[use->i])
	{
		if (!(tmp = malloc(sizeof(char) * ft_strlen_to_char(&r[use->i]))))
			return (NULL);
		if ((r[use->i] == '>' && r[use->i + 1] == '>') ||
				(r[use->i] == '>' || r[use->i] == '<'))
			use->sign = pars_red_norm(r, use);
		else if (r[use->i] != '>' && r[use->i] != '<' && r[use->i] != '\t' &&
				r[use->i] != ' ' && r[use->i] != '\n' && r[use->i])
		{
			use->file_name = ft_strdup(pars_red_norm1(r, use, tmp));
			add_red(&lst->pipe->all->red,
					creat_node_r(use->sign, use->file_name));
			ft_stringdel(&use->sign);
			ft_stringdel(&use->file_name);
			use->i--;
		}
		free(tmp);
		use->i++;
	}
	lst->pipe->all = update_all(lst->pipe->all,
			use->cmd, use->arg, lst->pipe->all->red);
	return (lst);
}

int				norm_check3(char *free_sp, int i)
{
	if ((free_sp[i] == '>' && free_sp[i + 1] == '>') || (free_sp[i] == '>'
				|| free_sp[i] == '<'))
		return (1);
	return (0);
}

int				norm_check5(char free_sp)
{
	if (free_sp != '>' && free_sp != '<' && free_sp != '\t' &&
		free_sp != ' ' && free_sp != '\n' && free_sp)
		return (1);
	return (0);
}

t_list_cmd		*redirection_sort(t_list_cmd *lst, t_use *use, char *free_sp)
{
	char *tmp;

	while (free_sp[use->i])
	{
		tmp = malloc(sizeof(char) * (ft_strlen_to_char(&free_sp[use->i]) + 1));
		if (norm_check3(free_sp, use->i))
			use->sign = pars_red_norm(free_sp, use);
		else if (norm_check5(free_sp[use->i]))
		{
			use->file_name = ft_strdup(pars_red_norm1(free_sp, use, tmp));
			add_red(&lst->all->red, creat_node_r(use->sign, use->file_name));
			ft_stringdel(&use->sign);
			ft_stringdel(&use->file_name);
			use->i--;
			free(tmp);
			tmp = NULL;
		}
		if (tmp)
			ft_stringdel(&tmp);
		use->i++;
	}
	lst->all = update_all(lst->all, use->cmd, use->arg, lst->all->red);
	return (lst);
}
