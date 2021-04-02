/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:17:22 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/08 12:08:27 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					check_int(char *p)
{
	int				i;

	i = 0;
	while (p[i])
	{
		if ((p[i] != '-' && p[i] < '0') || p[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long double			ft_atoi_loong(char *str)
{
	long double		ret;
	int				sign;
	int				i;

	i = 0;
	ret = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret * sign);
}

long long			ft_atoi_loong1(char *str)
{
	long long		ret;
	int				sign;
	int				i;

	i = 0;
	ret = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret * sign);
}

void				req_error(void)
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("numeric argument required", 2);
	exit(255);
}

void				ft_exit(t_all *all)
{
	char			**tmp;

	if (all->argument)
	{
		tmp = ft_split(all->argument, ' ');
		if (count_line(tmp) > 1 && check_int(tmp[0]) == 1)
			ft_putendl_fd("exit: too many arguments", 2);
		else if (count_line(tmp) != 0 && check_int(tmp[0]) == 0)
			req_error();
		else if ((ft_atoi_loong(all->argument) > 9223372036854775807))
			req_error();
		else if (count_line(tmp) == 1 && check_int(tmp[0]) == 1)
		{
			ft_putendl_fd("exit", 1);
			exit(ft_atoi_loong1(all->argument));
		}
		ft_free_2dem_arr((void ***)&tmp);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
}
