/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/13 17:17:08 by kpires           ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_global	global;
	char		*line;
	t_state		state;

	init_global(&global, env, av);
	while (ac && av)
	{
		line = readline("$> ");
		if (!line)
			break ;
		add_history(line);
		global.cmds = parse_input(&global, line, global.env_list, 0);
		print_test(&global);
		char *cmd_arr[] = {global.cmds[0]->exec, global.cmds[0]->args, NULL};
		state = ft_redir(&global);
		printf("state: %d\n", state);
		if (gest_builtins(global.env_list, cmd_arr) == NONE)
			gest_shell(global.env_list, cmd_arr);
		free_cmds(global.cmds);
	}
	rl_clear_history();
	return (free_list(global.env_list), 0);
}
