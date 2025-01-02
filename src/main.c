/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/02 23:03:49 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;

static void	handl_int(int sig)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (wait(NULL) == -1)
		rl_redisplay();
	g_signal = sig;
}

static void	handl_quit(int sig)
{
	rl_on_new_line();
	if (wait(NULL) == -1)
	{
		printf("\e[2K\r");
		rl_redisplay();
	}
	else
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	g_signal = sig;
}

void	signal_ctrd(t_global *g)
{
	printf("exit\n");
	free_cmds(g);
	clear_history();
	rl_clear_history();
	exit(g->exit_val);
}

/*
voir ft_one
ctrl d probleme de free segfault free cmds

EXPANDER
$EMPTY -> sortis vide
$EMPTY echo hi -> hi
bash-5.1$ "" ls
bash: : command not found
*/

int	main(int ac, char **av, char **env)
{
	t_env		*list;
	t_global	g;
	char		*line;

	list = arr2list(env);
	g.exit_val = 0;
	while (ac && av)
	{
		g_signal = 0;
		(signal(SIGINT, handl_int), signal(SIGQUIT, handl_quit));
		line = readline("$> ");
		if (!is_syntax_valid(&g, line, list))
		{
			free(line);
			continue ;
		}
		init_s_cmd(&g, line);
		if (ft_redir(&g, list, -1, 0))
			ft_exec(&g, list);
		else
			g.exit_val = 2;
		(free(line), free_cmds(&g));
	}
	(clear_history(), rl_clear_history());
	return (free_cmds(&g), free_list(list), 0);
}
