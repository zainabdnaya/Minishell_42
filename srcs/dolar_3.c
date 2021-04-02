/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:23:18 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:33:38 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tmp			*norm_case04(t_dolar *dol, char *s, char *tmp)
{
	if (dol->u == 0)
	{
		dol->m = (dol->u - 1) / 2;
		while (dol->i < dol->i + dol->m)
		{
			{
				tmp[dol->k++] = '$';
				dol->i++;
			}
		}
		tmp[dol->k] = '\0';
		dol->c1 = creat_tmp(tmp);
	}
	else
	{
		while (s[dol->i] != '$' && s[dol->i])
			tmp[dol->k++] = s[dol->i++];
		tmp[dol->k] = '\0';
		dol->c1 = creat_tmp(tmp);
	}
	return (dol->c1);
}

t_tmp			*norm_case00_4(t_dolar *dol, char *s, char *tmp)
{
	while (s[dol->i] == '\\' && s[dol->i])
	{
		tmp[dol->k++] = s[dol->i++];
		dol->w++;
	}
	if (dol->w % 2 == 0)
	{
		if (s[dol->i] == '$')
			dol->c1 = creat_tmp(tmp);
		else
		{
			while ((s[dol->i] != '$' && s[dol->i] != '\"' && s[dol->i] != '\'')
					&& s[dol->i])
				tmp[dol->k++] = s[dol->i++];
			tmp[dol->k] = '\0';
			dol->c1 = creat_tmp(tmp);
		}
	}
	else
	{
		tmp[dol->k++] = s[dol->i++];
		tmp[dol->k] = '\0';
		dol->c1 = creat_tmp(tmp);
	}
	return (dol->c1);
}

t_tmp			*case_04(t_dolar *dol, char *s, char *tmp)
{
	dol->w = 0;
	dol->k = 0;
	if (s[dol->i] == '$' && s[dol->i + 1] == '\\')
		tmp[dol->k++] = s[dol->i++];
	if (s[dol->i] == '\\')
		return (norm_case00_4(dol, s, tmp));
	return (norm_case04(dol, s, tmp));
}

t_tmp			*case_05(t_dolar *dol, char *s, char *tmp)
{
	while (s[dol->i] == '$' && s[dol->i + 1] == '$')
		tmp[dol->k++] = s[dol->i++];
	tmp[dol->k] = '\0';
	dol->c1 = creat_tmp(tmp);
	return (dol->c1);
}

t_tmp			*case_06(t_dolar *dol, char *s, char *tmp)
{
	while ((s[dol->i] != '$' || (s[dol->i] == '$' && s[dol->i + 1] == '\"'))
			&& s[dol->i])
		tmp[dol->k++] = s[dol->i++];
	tmp[dol->k] = '\0';
	dol->c1 = creat_tmp(tmp);
	return (dol->c1);
}
