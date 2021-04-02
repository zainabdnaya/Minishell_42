/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolars_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:24:29 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:36:27 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tmp			*case_00(t_dolar *dol, t_path *path, char *s)
{
	if ((s[dol->i] == '$' && s[dol->i + 1] == '?'))
	{
		dol->two = ft_itoa(path->dol_sign);
		dol->c1 = creat_tmp(dol->two);
	}
	if (s[dol->i] == '$' && (s[dol->i + 1] == '\0' || s[dol->i + 1] == '\n'))
		dol->c1 = creat_tmp(ft_strdup("$"));
	if (s[dol->i] == '$' && s[dol->i + 1] == '/')
		dol->c1 = creat_tmp(ft_strdup("$/"));
	dol->i++;
	return (dol->c1);
}

t_tmp			*case_011(t_dolar *dol, char *s, char *tmp1, t_path *path)
{
	char *tmp;

	if ((ft_isalpha2(s[dol->i]) == 1 ||
				ft_isdigit(s[dol->i]) == 1 || s[dol->i] == '_')
			&& s[dol->i])
	{
		while ((ft_isalpha2(s[dol->i]) == 1 ||
					ft_isdigit(s[dol->i]) == 1 || s[dol->i] == '_')
				&& s[dol->i])
			tmp1[dol->k++] = s[dol->i++];
		tmp1[dol->k] = '\0';
		tmp = search_env(path->env->fullenv, tmp1);
		dol->var_tmp = join_dolar(dol->s1, tmp);
		dol->c1 = creat_tmp(dol->var_tmp);
	}
	else
	{
		tmp1 = NULL;
		dol->var_tmp = join_dolar(dol->s1, NULL);
		dol->c1 = creat_tmp(dol->var_tmp);
	}
	return (dol->c1);
}

t_tmp			*case_01(t_dolar *dol, char *s, char *tmp1, t_path *path)
{
	dol->i++;
	dol->u = (dol->w - 1) / 2;
	if (!(dol->s1 = malloc(sizeof(char) * (dol->u + 1))))
		return (NULL);
	dol->i = dol->i + dol->u;
	if (dol->u != 0)
	{
		while (s[dol->i] == '$' && s[dol->i])
			dol->s1[dol->k++] = s[dol->i++];
		dol->s1[dol->k] = '\0';
	}
	dol->k = 0;
	dol->c1 = case_011(dol, s, tmp1, path);
	return (dol->c1);
}

t_tmp			*case_02(t_dolar *dol, char *s, char *tmp1)
{
	dol->u = (dol->w) / 2;
	dol->i = dol->i + dol->u;
	if (!(dol->s1 = malloc(sizeof(char) * (dol->u + 1))))
		return (NULL);
	while (s[dol->i] == '$' && s[dol->i])
	{
		dol->s1[dol->k++] = '$';
		dol->i++;
	}
	dol->s1[dol->k] = '\0';
	dol->k = 0;
	while ((s[dol->i] != '$' || (s[dol->i] == '$' && s[dol->i + 1] == '\"'))
			&& s[dol->i])
		tmp1[dol->k++] = s[dol->i++];
	tmp1[dol->k] = '\0';
	dol->c1 = creat_tmp(join_dolar(dol->s1, tmp1));
	return (dol->c1);
}

t_tmp			*case_03(t_dolar *dol, char *s, char *tmp)
{
	dol->k = 0;
	if (dol->i == 0)
		dol->j = spl_quote(s, dol->i + 1) + 1 + dol->i;
	else
		dol->j = spl_quote(s, dol->i + 1) + dol->i;
	while (dol->i < dol->j && s[dol->i])
	{
		tmp[dol->k++] = s[dol->i++];
	}
	tmp[dol->k] = '\0';
	dol->c1 = creat_tmp(tmp);
	return (dol->c1);
}
