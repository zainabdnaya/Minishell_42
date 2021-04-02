/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_antislach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:34:49 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:23:33 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*no_slash_norm(char *str, t_use *use, char *tmp)
{
	use->u = 0;
	use->w = 0;
	use->j = 0;
	if (!(use->str1 = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	use->str1[use->j++] = str[use->i++];
	while (str[use->i] != 34 && str[use->i])
	{
		if (str[use->i] == '\\')
		{
			if (is_valid(str[use->i + 1]))
				use->str1[use->j++] = str[use->i++];
			else
			{
				use->str1[use->j++] = str[++use->i];
				use->i++;
			}
		}
		if (str[use->i] != '\\')
			use->str1[use->j++] = str[use->i++];
	}
	use->str1[use->j++] = str[use->i++];
	use->str1[use->j] = '\0';
	tmp = join_dolar(tmp, use->str1);
	return (tmp);
}

char		*slach_12(char *str, t_use *use)
{
	if (use->w % 2 != 0)
	{
		use->i++;
		use->u = (use->w - 1) / 2;
		if (!(use->s1 = malloc(sizeof(char) * (use->u + 1))))
			return (NULL);
		use->i = use->i + use->u;
		if (use->u != 0)
		{
			while (str[use->i] == '\\' && str[use->i])
				use->s1[use->k++] = str[use->i++];
			use->s1[use->k] = '\0';
		}
	}
	return (use->s1);
}

char		*no_slash_norm1(char *str, t_use *use, char *tmp)
{
	use->w = count_slash(str, use->i);
	use->s1 = slach_12(str, use);
	if (use->w % 2 == 0)
	{
		use->u = (use->w) / 2;
		if (!(use->s1 = malloc(sizeof(char) * (use->u + 1))))
			return (NULL);
		use->i = use->i + use->u;
		while (str[use->i] == '\\' && str[use->i])
			use->s1[use->k++] = str[use->i++];
		use->s1[use->k] = '\0';
	}
	tmp = join_dolar(tmp, use->s1);
	return (tmp);
}

char		*no_slash_norm2(char *str, t_use *use, char *tmp)
{
	use->j = 0;
	if (str[use->i] == '\'')
	{
		use->u = spl_quote(str, use->i + 1) + 1;
		if (!(use->str1 = malloc(sizeof(char) * (use->u + 1))))
			return (NULL);
		while (use->i < use->u && str[use->i])
			use->str1[use->j++] = str[use->i++];
		use->str1[use->j] = '\0';
	}
	else
	{
		if (!(use->str1 = malloc(sizeof(char) *
						(alloc_slach(str, use->i) + 1))))
			return (NULL);
		while (str[use->i] != '\\' && str[use->i])
			use->str1[use->j++] = str[use->i++];
		use->str1[use->j] = '\0';
	}
	tmp = join_dolar(tmp, use->str1);
	return (tmp);
}
