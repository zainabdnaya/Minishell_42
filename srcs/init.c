/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:10:45 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/07 10:26:22 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		init(t_path *path)
{
	path->ret = 0;
	path->dos = 0;
	path->ret = 0;
	path->p = NULL;
	path->dol_sign = 0;
	path->p = NULL;
	path->env = malloc(sizeof(t_env));
}

void		sh_initial(t_shell *sh)
{
	t_dol dol;

	dol.dol_s = 0;
	sh->pipe = 0;
	sh->comma = 0;
	sh->count_pipe = 0;
	sh->both = 0;
	sh->redirection = 0;
	sh->count_comma = 0;
	sh->sp_quote = 0;
	sh->db_quote = 0;
	sh->error = 0;
}
