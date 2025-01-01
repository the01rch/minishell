/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/01 18:05:20 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;

static void	handler_sigint(int sig)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (wait(NULL) == -1)
		rl_redisplay();
	g_signal = sig;
}

static void	handler_sigquit(int sig)
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
	rl_clear_history();
	exit(g->exit_val);
}

int	main(int ac, char **av, char **env)
{
	t_env		*list;
	t_global	global;
	char		*line;

	list = arr2list(env);
	global.exit_val = 0;
	while (ac && av)
	{
		g_signal = 0;
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, handler_sigquit);
		line = readline("$> ");
		if (!is_syntax_valid(&global, line, list))
		{
			free(line);
			continue ;
		}
		init_s_cmd(&global.cmds, line, &global.cnt);
		if (ft_redir(&global, list, -1, 0))
			ft_exec(&global, list);
		else
			global.exit_val = 2;
		(free(line), free_cmds(&global));
	}
	return (rl_clear_history(), free_list(list), 0);
}
