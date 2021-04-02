/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:08:10 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/08 11:53:12 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_var_glob1;

void			sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_var_glob1 = 1;
		g_var_glob2 = 1;
		ft_putstr_fd("\b\b  \b\b\n\e[1;32mbash$ \e[0;37m", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (g_var_glob1 == 3)
			g_var_glob2 = 2;
		ft_putstr_fd("\b\b  \b\b", 1);
	}
}

void			ft_exe(t_shell *sh, t_path *path, t_list_cmd *lst, t_read *rd)
{
	if (sh->error != 1 && !path->dos)
	{
		if (g_var_glob2 == 1)
		{
			path->dol_sign = 1;
			g_var_glob2 = 0;
		}
		if (g_var_glob2 == 2)
		{
			path->dol_sign = 131;
			g_var_glob2 = 0;
		}
		if (g_var_glob2 == 0)
			g_var_glob1 = 3;
		lst = handle_line(rd, lst);
		if (check_one(rd->line) == 1)
			pipes_cmd1(path, lst, sh);
		else if (check_one(rd->line) == 3)
			call_pipe(lst, path, sh);
		else
			call_getprg(lst, path, sh);
		free_lst(lst);
	}
	else
		path->dol_sign = 258;
}

void			get_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}

void			prompt(t_path *path, t_read *rd, t_shell *sh, t_list_cmd *lst)
{
	while (1)
	{
		if (!path->dos && g_var_glob1 != 1)
			ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 1);
		rd->line = malloc(sizeof(char) * BUFFER_SIZE);
		ft_bzero(rd->line, sizeof(char) * BUFFER_SIZE);
		path->ret = read(0, rd->line, BUFFER_SIZE);
		ctrl_d(rd, path);
		g_var_glob1 = 3;
		if (rd->line[0] != '\n')
		{
			sh_initial(sh);
			check_line_error(rd->line, sh);
			ft_exe(sh, path, lst, rd);
			if (g_var_glob2 == 2)
				ft_putstr_fd("Quit: 3\n", 1);
		}
		ft_free_arr((void **)&rd->line);
	}
}

int				main(int argc, char **argv, char **env)
{
	t_read				rd;
	t_shell				sh;
	t_list_cmd			lst;
	t_path				path;

	g_var_glob1 = 0;
	g_var_glob1 = 0;
	(void)argc;
	(void)argv;
	init(&path);
	get_signals();
	path.env->fullenv = ft_strdup_2d(env);
	rd.line = NULL;
	prompt(&path, &rd, &sh, &lst);
}
