/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_antislash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:17:48 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:16:54 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*slach_norm04(char *str, t_use *use)
{
	use->j = 0;
	if (!(use->str1 = malloc(sizeof(char) * (alloc_slach(str, use->i) + 1))))
		return (NULL);
	while (str[use->i] != '\\' && str[use->i])
		use->str1[use->j++] = str[use->i++];
	use->str1[use->j] = '\0';
	return (use->str1);
}

char		*slach_norm002(char *str, t_use *use, char *tmp)
{
	char *tmp1;

	use->k = 0;
	use->w = count_slash(str, use->i);
	if (use->w % 2 != 0)
		use->s1 = slach_norm02(str, use);
	else if (use->w % 2 == 0)
		use->s1 = slach_norm03(str, use);
	tmp1 = tmp;
	tmp = join_dolar(tmp, use->s1);
	ft_stringdel(&tmp1);
	ft_stringdel(&use->s1);
	return (tmp);
}

char		*norm_tmp(t_use *use, char *str, char *tmp)
{
	char *tmp1;

	use->str1 = slach_norm04(str, use);
	tmp1 = tmp;
	tmp = join_dolar(tmp, use->str1);
	ft_stringdel(&tmp1);
	return (tmp);
}

char		*no_antislach(char *string)
{
	char		*str;
	char		*tmp;
	t_use		use;

	ft_bzero(&use, sizeof(t_use));
	str = ft_strdup(string);
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[use.i] != '\0')
	{
		if (str[use.i] == '\"')
			tmp = no_slash_norm(str, &use, tmp);
		if (str[use.i] == '\'')
			tmp = slash_norm001(str, &use);
		if (str[use.i] == '\\')
			tmp = slach_norm002(str, &use, tmp);
		else
			tmp = norm_tmp(&use, str, tmp);
	}
	ft_stringdel(&str);
	ft_stringdel(&use.str1);
	return (tmp);
}
