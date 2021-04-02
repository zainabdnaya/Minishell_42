/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:57:34 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 17:48:44 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_dolar(t_tmp **dol)
{
	t_tmp *tmp;

	while (*dol)
	{
		tmp = (*dol)->next;
		if ((*dol)->s1)
		{
			free((*dol)->s1);
			(*dol)->s1 = NULL;
		}
		free(*dol);
		*dol = tmp;
	}
	*dol = NULL;
}

void		free_all_node(t_all **all)
{
	if ((*all)->command != NULL)
	{
		free((*all)->command);
		(*all)->command = NULL;
	}
	if ((*all)->argument != NULL)
	{
		free((*all)->argument);
		(*all)->argument = NULL;
	}
	free(*all);
	*all = NULL;
}

void		ft_stringdel(char **string)
{
	if (*string)
	{
		free(*string);
		*string = NULL;
	}
}

int			check_0(char *line)
{
	int		i;

	i = 0;
	while (((line[i] != '<' && line[i] != '>')) && line[i])
		i++;
	if ((line[i] == '>' && line[i + 1] == '>'))
		i = i + 2;
	else if ((line[i] == '>' || line[i] == '<'))
		i++;
	while ((line[i] == ' ' || line[i] == '\t') && line[i])
		i++;
	if (line[i] == ';' || line[i] == '|')
	{
		write(1, "syntax error\n", 14);
		return (1);
	}
	else
		return (0);
}
