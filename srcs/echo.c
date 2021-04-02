/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:02:30 by zjamali           #+#    #+#             */
/*   Updated: 2021/03/07 11:39:53 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			check_n(char *str)
{
	int			i;

	i = 0;
	if (str[i++] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

char		*conver_free(char **spl, int i, t_path *path)
{
	char			*tmp;

	tmp = spl[i];
	spl[i] = replace_01(spl[i], path);
	ft_stringdel(&tmp);
	tmp = spl[i];
	spl[i] = slach((spl[i]));
	ft_stringdel(&tmp);
	tmp = spl[i];
	spl[i] = no_quote(spl[i]);
	ft_stringdel(&tmp);
	return (spl[i]);
}

void		ft_put_str(char **spl, int i, t_path *path, int j)
{
	while (spl[i])
	{
		if (i != j)
			spl[i] = conver_free(spl, i, path);
		ft_putstr_fd(spl[i], 1);
		if (spl[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
}

void		ft_echo(char *str, int option, t_path *path)
{
	char		**spl;
	int			i;
	int			j;

	i = -1;
	j = -1;
	if (!(spl = shell_space_split(str)))
		return ;
	while (spl[++i])
	{
		spl[i] = conver_free(spl, i, path);
		if (check_n(spl[i]) == 0)
		{
			j = i;
			break ;
		}
		else if (check_n(spl[i]) == 1)
			option = 0;
	}
	ft_put_str(spl, i, path, j);
	if (option != 0)
		write(1, "\n", 2);
	path->dol_sign = 0;
	ft_free_2dem_arr((void ***)&spl);
}
