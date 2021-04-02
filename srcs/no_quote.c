/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:56:28 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:20:40 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			exist_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char		*spl(char *str, int *i, char *result, int *j)
{
	(*i)++;
	if (str[*i] != 39)
	{
		while ((*i) < spl_quote(str, (*i)))
			result[(*j)++] = str[(*i)++];
	}
	return (result);
}

char		*dbl(char *str, int *i, char *result, int *j)
{
	(*i)++;
	if (str[*i] != 34)
	{
		while ((*i) < dbl_quote(str, (*i)))
			result[(*j)++] = str[(*i)++];
	}
	return (result);
}

char		*noo_quote(char *s)
{
	int			i;
	int			j;
	char		*result;
	char		*res;
	char		*str;

	i = 0;
	j = 0;
	str = ft_strdup(s);
	if (!(result = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			result = spl(str, &i, result, &j);
		else if (str[i] == '\"')
			result = dbl(str, &i, result, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	ft_stringdel(&str);
	res = ft_strtrim(result, "\n");
	ft_stringdel(&result);
	return (res);
}

char		*no_quote(char *s)
{
	if (witch_quote(s, 0) != '\0')
		return (noo_quote(s));
	else
		return (ft_strdup(s));
}
