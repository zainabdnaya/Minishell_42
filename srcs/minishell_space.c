/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:27:51 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:10:46 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			len_each(const char *s, int i)
{
	int			len;

	len = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
	{
		i++;
		len++;
	}
	return (len);
}

int			each_char_norm(int i, int u, int z)
{
	if (u % 2 != 0)
		return (i + 1);
	else if (u % 2 == 0 && z == 0)
		return (i + 1);
	else
		return (i);
}

int			each_char(const char *s, int i)
{
	int			z;
	int			u;
	int			len;

	z = 0;
	len = len_each(s, i);
	i = len + i;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		if (s[i] == '\\')
		{
			u = dbl_quote_norm(s, &i);
			i = u + i;
			if (s[i] == ' ' || s[i] == '\t')
				z = 1;
			if (u % 2 == 0 && z == 1)
				return (i);
			else
				i = norm_ligne3(s, i, u);
		}
		else
			i = norm_ligne2(s, i);
		i++;
	}
	return (i - len);
}

char		**colomn(char **array, const char *s, int y, int w)
{
	t_use			use;

	ft_bzero(&use, sizeof(t_use));
	while (s[use.o] && (s[use.o] == ' ' || s[use.o] == '\t'))
		use.o++;
	while (w < y)
	{
		use.i = 0;
		if (!(array[w] = malloc(sizeof(char) *
								(each_char(s, use.o) - use.k + 1))))
			free_2d_char(&(array), w);
		use.k = each_char(s, use.o);
		while (s[use.o] && use.o < use.k)
			array[w][use.i++] = s[use.o++];
		array[w][use.i] = '\0';
		while (s[use.o] && (s[use.o] == ' ' || s[use.o] == '\t'))
			use.o++;
		w++;
	}
	array[w] = NULL;
	return (array);
}

char		**shell_space_split(const char *line)
{
	char		**array;
	int			y;
	int			w;

	w = 0;
	y = 0;
	y = ligne(line);
	if (!(array = malloc(sizeof(char *) * (y + 1))))
		return (NULL);
	return (colomn(array, line, y, w));
}
