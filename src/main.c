/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/30 15:43:42 by redrouic         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_env		*list;
	t_cmd		*cmd;
	char		*line;

	list = arr2list(env);
	while (ac && av)
	{
		g_signal = 0;
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, handler_sigquit);
		line = readline("$> ");
		if (!line)
			return (free(line), free_list(list), printf("exit\n"), exit(1), 0);
		if (!is_syntax_valid(line))
		{
			free(line);
			continue ;
		}
		init_s_cmd(list, &cmd, line);
		/*
		if (ft_redir(cmd, list))
			ft_exec(*cmd, list);
			*/
		(free(line));
	}
	return (rl_clear_history(), free_list(list), 0);
}
