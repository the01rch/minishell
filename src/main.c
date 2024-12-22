/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/22 01:33:56 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

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
	printf("redir :%s\n", cmd->redir);
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (printf(EALL), exit(1), (void)0);
	ft_strncpy(tmp, line, i);
	cmd->args = str2arr(tmp, " \t", true);
	free(tmp);
	if (!cmd->args)
		return (printf(EALL), exit(1), (void)0);
	i = 0;
	while (cmd->args[i] != NULL)
	{
		printf("args[%d] :%s\n", i, cmd->args[i]);
		i++;
	}
}

t_state	gest_builtins(t_env *lenv, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd->args[0], "exit"))
	{
		if (cmd->args[1])
			return (printf("exit: too many arguments\n"), ERROR);
		printf("exit\n");
		free_list(lenv);
		exit(1);
	}
	if (ft_strcmp(cmd->args[0], "echo"))
	{
		i++;
		if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n"))
			i++;
		while (cmd->args[i] != NULL)
			printf("%s ", cmd->args[i++]);
		if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n"))
			return (VALID);
		return (printf("\n"), VALID);
	}
	return (gest_env(lenv, cmd->args));
}

// TODO [ ] create free cmd struct
// 		[.] finishing expander
// 		[ ] env -i
// 		[ ] handling signals
// 		[ ] fix leaks

int	g_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_env		*list;
	t_cmd		cmd;
	char		*line;

	list = arr2list(env);
	while (ac && av)
	{
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, handler_sigquit);
		g_signal = 0;
		line = readline("$> ");
		if (!line)
		{
			printf("exit\n");
			exit(1);
		}
		if (!is_syntax_valid(line))
		{
			free(line);
			continue ;
		}
		fill_s_cmd(&cmd, line);
		if (ft_redir(&cmd, list))
			ft_exec(cmd, list);
		free_cmd(&cmd);
		free(line);
	}
	rl_clear_history();
	free_list(list);
	return (0);
}
