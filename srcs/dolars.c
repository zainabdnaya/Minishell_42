/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:50:18 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:39:03 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tmp		*dolar_norm(char *s, t_path *path, t_dolar *dol)
{
	dol->k = 0;
	dol->w = 0;
	if (!(dol->tmp1 = malloc(sizeof(char) * (in_dollar(s, dol->i) + 1))))
		return (NULL);
	dol->w = count_dolars(s, dol->i);
	if (dol->w % 2 != 0)
		return (case_01(dol, s, dol->tmp1, path));
	else
		return (case_02(dol, s, dol->tmp1));
}

t_tmp		*dolar_norm1(char *s, t_path *path, t_dolar *dol)
{
	dol->k = 0;
	dol->w = 0;
	if (!(dol->tmp = malloc(sizeof(char) * (until_dollar(s, dol->i) + 1))))
		return (NULL);
	return (norm_case_00_7(dol, s, dol->tmp, path));
}

t_tmp		*dolar_norm2(char *s, t_dolar *dol)
{
	dol->k = 0;
	dol->w = 0;
	if (!(dol->tmp = malloc(sizeof(char) * (until_dollar(s, dol->i) + 1))))
		return (NULL);
	if (s[dol->i] == '\'')
	{
		dol->res_tmp = case_03(dol, s, dol->tmp);
		dol->o = 1;
	}
	if ((s[dol->i] == '$' && s[dol->i + 1] == '\\') || s[dol->i] == '\\')
	{
		dol->res_tmp = case_04(dol, s, dol->tmp);
		dol->o = 1;
	}
	if (s[dol->i] == '$' && s[dol->i + 1] == '$')
	{
		dol->res_tmp = case_05(dol, s, dol->tmp);
		dol->o = 1;
	}
	if (dol->o != 1)
		dol->res_tmp = case_06(dol, s, dol->tmp);
	return (dol->res_tmp);
}

t_tmp		*dolar_last(char *s, t_path *path, t_dolar *dol)
{
	while (s[dol->i])
	{
		if (condition_norm01(s, dol->i) == 1)
			dol->res_tmp = case_00(dol, path, s);
		else if (s[dol->i] == '$' && s[dol->i + 1] != '\\')
		{
			dol->res_tmp = dolar_norm(s, path, dol);
			--dol->i;
		}
		else if (s[dol->i] == '\"')
		{
			dol->res_tmp = dolar_norm1(s, path, dol);
			if (s[dol->i] != '\0')
				--dol->i;
		}
		else if (condition_norm01(s, dol->i) == 2)
		{
			dol->res_tmp = dolar_norm2(s, dol);
			--dol->i;
		}
		dol->o = 0;
		(s[dol->i]) ? dol->i++ : 0;
		add_tmp(&(dol->head), dol->res_tmp);
	}
	return (dol->head);
}

char		*dolar(char *str, t_path *path)
{
	t_dolar		dol;
	t_tmp		*tmp;
	char		*s;
	char		*result;

	s = ft_strdup(str);
	ft_bzero(&dol, sizeof(t_dolar));
	dol.head = NULL;
	dol.head = dolar_last(s, path, &dol);
	result = NULL;
	tmp = dol.head;
	while (dol.head != NULL)
	{
		result = join_dolar(result, dol.head->s1);
		dol.head = dol.head->next;
	}
	dol.head = tmp;
	free_dolar(&(dol.head));
	ft_stringdel(&s);
	free_str_dol(&dol);
	return (result);
}
