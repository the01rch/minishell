/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/23 23:03:22 by kpires           ###   ########.fr       */
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

static void	fill_redir(t_cmd *cmd, char *line, int len)
{
	int	i;

	if (len == (int)ft_strlen(line))
		cmd->redir = NULL;
	else if (len < (int)ft_strlen(line))
	{
		cmd->redir = malloc(sizeof(char) * (ft_strlen(line) - len + 1));
		if (!cmd->redir)
			return (printf("%s", EALL), exit(1), (void)0);
		i = 0;
		while (len < (int)ft_strlen(line))
			cmd->redir[i++] = line[len++];
		cmd->redir[i] = '\0';
	}
}

static void	fill_s_cmd(t_cmd *cmd, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	cmd->infile = -1;
	cmd->outfile = -1;
	while (line[i] && line[i] != '|')
	{
		if (is_chr("><", line[i]) && !inq(line, i, true))
			break ;
		i++;
	}
	fill_redir(cmd, line, i);
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (printf(EALL), exit(1), (void)0);
	ft_strncpy(tmp, line, i);
	cmd->args = str2arr(tmp, " \t", true);
	free(tmp);
	if (!cmd->args)
		return (printf(EALL), exit(1), (void)0);
}

int	main(int ac, char **av, char **env)
{
	t_env		*list;
	t_cmd		cmd;
	char		*line;

	list = arr2list(env);
	while (ac && av)
	{
		g_signal = 0;
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, handler_sigquit);
		line = readline("$> ");
		if (!line)
			return (printf("exit\n"), free_list(list), exit(1), 0);
		if (!is_syntax_valid(line))
		{
			free(line);
			continue ;
		}
		fill_s_cmd(&cmd, line);
		if (ft_redir(&cmd, list))
			ft_exec(cmd, list);
		(free_cmd(&cmd), free(line));
	}
	(free_list(list), rl_clear_history());
	return (0);
}
