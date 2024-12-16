/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/16 14:18:17 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

t_state	gest_builtins(t_env *lenv, char **arr)
{
	int	i;

	i = 0;
	if (ft_strcmp(arr[0], "exit"))
	{
		if (arr[1])
			return (printf("exit: too many arguments\n"), ERROR);
		printf("exit\n");
		free_arr(arr);
		free_list(lenv);
		exit(1);
	}
	if (ft_strcmp(arr[0], "echo"))
	{
		i++;
		if (arr[1] && ft_strcmp(arr[1], "-n"))
			i++;
		while (arr[i])
			printf("%s ", arr[i++]);
		if (arr[1] && ft_strcmp(arr[1], "-n"))
			return (free_arr(arr), VALID);
		return (free_arr(arr), printf("\n"), VALID);
	}
	return (gest_env(lenv, arr));
}
/*
t_command	**parse_input(t_global *global, char *line, t_env *env_list, int i)
{
	t_command	**cmds;
	char		**cmd_parts;

	global->full = str2arr(line, "|", true);
	cmds = malloc(sizeof(t_command *) * (count_rows("|", line, true) + 1));
	while (global->full[i])
	{
		cmds[i] = malloc(sizeof(t_command));
		cmds[i]->full = ft_strdup(global->full[i]);
		cmd_parts = str2arr(global->full[i], " ", true);
		cmds[i]->exec = ft_strdup(gest_sign(env_list, cmd_parts[0], 0));
		if (cmd_parts[1])
			cmds[i]->args = ft_strdup(gest_sign(env_list, global->full[i]
						+ strlen(cmd_parts[0]) + 1, 0));
		else
			cmds[i]->args = NULL;
		cmds[i]->infile = STDIN_FILENO;
		cmds[i]->outfile = STDOUT_FILENO;
		free_arr(cmd_parts);
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

static void	init_global(t_global *global, char **env, char **av)
{
	global->env = env;
	global->env_list = arr2list(env);
	global->pid = getpid();
	global->argv = av;
	listening();
}

static void	print_test(t_global *global)
{
	int	i;

	i = 0;
	while (global->cmds[i])
	{
		printf("cmds[%d]->exec :%s\n",
			i, global->cmds[i]->exec);
		if (global->cmds[i]->args)
			printf("cmds[%d]->args :%s\n", i, global->cmds[i]->args);
		if (global->cmds[i]->full)
			printf("cmds[%d]->full :%s\n", i, global->cmds[i]->full);
		i++;
	}
}

int	is_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set && set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

bool	gest_err(char *str)
{
	while (*str == '\t' || *str == 32)
		str++;
	if (*str == '|')
		return (perror("error: pipe\n"), true);
	if (*str && !is_in_set(*str, "><|\"'"))
		str++;
	return (false);
}

*/
int	main(int ac, char **av, char **env)
{
	t_env		*list;
	char		**cmd;
	char		*line;

	list = arr2list(env);
	while (ac && av)
	{
		line = readline("$> ");
		add_history(line);
		/*
		if (gest_err(line))
			continue ;
			*/
		cmd = str2arr(line, " \t", true);
		if (gest_builtins(list, cmd) == NONE)
		{
			gest_shell(list, cmd);
			free_arr(cmd);
		}
	}
	rl_clear_history();
	free_list(list);
	return (0);
}
