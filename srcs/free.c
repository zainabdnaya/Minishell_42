/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:48:06 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:52:13 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_str_dol(t_dolar *dol)
{
	if (dol->tmp)
		ft_stringdel(&dol->tmp);
	if (dol->tmp1)
		ft_stringdel(&dol->tmp1);
	if (dol->var)
		ft_stringdel(&dol->var);
	if (dol->var_tmp)
		ft_stringdel(&dol->var_tmp);
	if (dol->result)
		ft_stringdel(&dol->result);
	if (dol->two)
		ft_stringdel(&dol->two);
	if (dol->s1)
		ft_stringdel(&dol->s1);
	if (dol->tmp2)
		ft_stringdel(&dol->tmp2);
}

void	free_1d(char *p)
{
	if (p)
	{
		free(p);
		p = NULL;
	}
}

void	free_2d_char(char ***array, int len)
{
	int i;

	i = 0;
	if (*array == NULL)
		return ;
	while (i < len)
	{
		if ((*array)[i])
		{
			free((*array)[i]);
			(*array)[i] = NULL;
		}
		i++;
	}
	free(*array);
	*array = NULL;
}

void	ft_free_arr(void **array)
{
	if (*array)
		free(*array);
	*array = NULL;
}

void	ft_free_2dem_arr(void ***arr)
{
	int i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
