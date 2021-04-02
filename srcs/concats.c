/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:30:44 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/06 12:51:59 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	if ((!s1 || !s2))
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (((s1[i] == '\0' && s2[i] != '\0') || (s2[i] == '\0' && s1[i] != '\0')))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char	*ft_str_join(char *s1, char *s2, char *s3)
{
	char *result;
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	result = ft_strjoin(tmp, s3);
	ft_stringdel(&tmp);
	return (result);
}

char	*concat(char **tmp, int i)
{
	char *result;
	char *tmp1;

	result = NULL;
	if (tmp[i] == NULL)
		return (NULL);
	while (tmp[i] != NULL)
	{
		tmp1 = result;
		result = concat_space((tmp[i]), result);
		ft_stringdel(&tmp1);
		i++;
	}
	return ((result));
}

char	*concat_space(char *tmp, char *tmp1)
{
	char *result;

	if (tmp1 == NULL && tmp == NULL)
		return (NULL);
	if (tmp1 == NULL && tmp != NULL)
		result = ft_strdup(tmp);
	else if (tmp1 != NULL && tmp == NULL)
		result = ft_strdup(tmp1);
	else
		result = ft_str_join(tmp1, " ", tmp);
	return ((result));
}
