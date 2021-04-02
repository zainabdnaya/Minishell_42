/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:14:03 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 15:44:23 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		condition_norm01(char *s, int i)
{
	if ((s[i] == '$' && s[i + 1] == '?') ||
			(s[i] == '$' && (s[i + 1] == '\0' || s[i + 1] == '\n')) ||
			(s[i] == '$' && s[i + 1] == '/'))
		return (1);
	if (((s[i] != '$' && s[i] != '\"') || (s[i] == '$' && s[i + 1] == '\\')) &&
			s[i])
		return (2);
	if (((s[i] != '$') || (s[i] == '$' && s[i + 1] == '\\') ||
				(s[i] == '$' && is_valid(s[i + 1]) == 0)) &&
			s[i])
		return (3);
	else
		return (0);
}

char	*join_dolar(char *s1, char *s2)
{
	char			*s3;
	unsigned int	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	len = 0;
	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	while (*s1)
		s3[len++] = *(s1++);
	while (*s2)
		s3[len++] = *(s2++);
	s3[len] = '\0';
	return (s3);
}

int		count_dolars(char *s, int i)
{
	int j;

	j = 0;
	while (s[i] == '$' && s[i])
	{
		j++;
		i++;
	}
	return (j);
}

int		search_norm1(char *line, int i, int u)
{
	if (line[i] == '\\')
	{
		while (line[i] == '\\' && line[i])
		{
			u++;
			i++;
		}
		return (u);
	}
	if (line[i] == '\\' && line[i + 1] == '$')
		i = i + 2;
	if (line[i] == '\'')
		i = spl_quote(line, i + 1) + 1;
	return (i);
}

int		serach_dolar(char *line)
{
	int i;
	int u;

	i = 0;
	u = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			u = search_norm1(line, i, u);
			i = i + u;
			if (u % 2 != 0)
				i++;
			else if (u % 2 == 0)
				continue;
		}
		i = search_norm1(line, i, u);
		if (i == -1)
			return (1);
		if (line[i] == '$' && line[i + 1] != '\\')
			return (1);
		i++;
	}
	return (0);
}
