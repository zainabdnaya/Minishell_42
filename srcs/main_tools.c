/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:55:38 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/07 10:36:20 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			**ft_strdup_2d(char **str)
{
	int			len;
	char		**ret;
	int			i;

	i = 0;
	len = count_line(str);
	ret = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void			ft_free_ex(t_path *path)
{
	ft_putendl_fd("exit", 1);
	ft_free_2dem_arr((void ***)&path->env->fullenv);
	exit(0);
}

void			ctrl_d(t_read *rd, t_path *path)
{
	char			*tmp;

	if (rd->line[0] == '\0' && !path->dos)
		ft_free_ex(path);
	if (rd->line[path->ret - 1] != '\n')
	{
		path->dos = 1;
		if (path->p)
			path->p = ft_strjoin(path->p, rd->line);
		else
			path->p = ft_strdup(rd->line);
	}
	else if (path->p && rd->line[path->ret - 1] == '\n')
	{
		tmp = path->p;
		path->p = ft_strjoin(path->p, rd->line);
		free(tmp);
		rd->line = ft_strdup(path->p);
		if (path->p)
		{
			free(path->p);
			path->p = NULL;
		}
		path->dos = 0;
	}
}
