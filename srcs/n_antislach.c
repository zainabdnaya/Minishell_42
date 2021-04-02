/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_antislach.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:11:16 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:16:07 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		alloc_norm(int *i, int *j, char *s)
{
	if (*i == 0)
	{
		if (s[*i] == '\'')
			*i = spl_quote(s, *i + 1);
		if (s[*i] == '\"')
		{
			*i = dbl_quote(s, *i + 1);
			*j = dbl_quote(s, *i + 1);
		}
	}
}

int			alloc_slach(char *s, int i)
{
	int j;

	j = 0;
	alloc_norm(&i, &j, s);
	while (s[i++])
	{
		if (s[i] == '\'' && i > 0 && s[i - 1] != '\\')
			i = spl_quote(s, i + 1);
		if (s[i] == '\"' && i > 0 && s[i - 1] != '\\')
		{
			i = dbl_quote(s, i + 1);
			j = dbl_quote(s, i + 1);
		}
		else
		{
			while (s[i] != '\\' && s[i])
			{
				j++;
				i++;
			}
			if (j != 0)
				return (j);
		}
	}
	return (j);
}

char		*slash_norm001(char *str, t_use *use)
{
	use->j = 0;
	use->u = spl_quote(str, use->i + 1) + 1;
	if (!(use->str1 = malloc(sizeof(char) * (use->u + 1))))
		return (NULL);
	while (use->i < use->u && str[use->i])
		use->str1[use->j++] = str[use->i++];
	use->str1[use->j] = '\0';
	return (use->str1);
}

char		*slach_norm02(char *str, t_use *use)
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
	return (use->s1);
}

char		*slach_norm03(char *str, t_use *use)
{
	use->u = (use->w) / 2;
	if (!(use->s1 = malloc(sizeof(char) * (use->u + 1))))
		return (NULL);
	use->i = use->i + use->u;
	while (str[use->i] == '\\' && str[use->i])
		use->s1[use->k++] = str[use->i++];
	use->s1[use->k] = '\0';
	return (use->s1);
}
