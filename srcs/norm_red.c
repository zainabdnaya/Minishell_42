/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:43:27 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 16:23:49 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*pars_red_norm(char *red, t_use *use)
{
	if (red[use->i] == '>' && red[use->i + 1] == '>')
	{
		ft_stringdel(&use->sign);
		use->sign = malloc(sizeof(char) * 3);
		use->sign[0] = red[use->i];
		use->sign[1] = red[use->i + 1];
		use->sign[2] = '\0';
		use->i = use->i + 1;
	}
	else if (red[use->i] == '>' || red[use->i] == '<')
	{
		ft_stringdel(&use->sign);
		use->sign = malloc(sizeof(char) * 2);
		use->sign[0] = red[use->i];
		use->sign[1] = '\0';
	}
	return (use->sign);
}
