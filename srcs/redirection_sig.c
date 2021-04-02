/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_sig.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:33:08 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:36:55 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			norm_checkz(char *tmp, int i)
{
	if ((tmp[i] == '>' && tmp[i + 1] != '>') || tmp[i] == '<' || tmp[i] == '>')
		return (1);
	return (0);
}

char		*seperat_red(char *tmp)
{
	int			i;
	int			j;
	char		*res;

	i = 0;
	j = 0;
	if (!(res = malloc(sizeof(char) * 2)))
		return (NULL);
	while (tmp[i] != '\0')
	{
		if (norm_checkz(tmp, i))
		{
			res[0] = tmp[i];
			res[1] = '\0';
			break ;
		}
		else if ((tmp[i] == '>' && tmp[i + 1] == '>'))
		{
			res = ft_strdup(">>");
			break ;
		}
		else
			i++;
	}
	return ((res));
}

char		*seperat_file_name(char *tmp)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!(res = malloc(sizeof(char) * (strlen(tmp)))))
		return (NULL);
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '<' || tmp[i] == '>')
			i++;
		else if ((tmp[i] == '>' && tmp[i + 1] == '>'))
			i = i + 2;
		else
		{
			res[j] = tmp[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	return ((res));
}
