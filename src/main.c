/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/19 14:04:47 by redrouic         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_env		*list;
	char		**cmd;
	char		*line;

	list = arr2list(env);
	while (ac && av)
	{
		line = readline("$> ");
		if (!is_syntax_valid(line))
			continue ;
		cmd = str2arr(line, " \t", true);
		if (!cmd)
			return (free_list(list), free_arr(cmd), perror(EALL), 1);
		if (gest_builtins(list, cmd) == NONE)
		{
			gest_shell(list, cmd);
			free_arr(cmd);
			cmd = NULL;
		}
	}
	free(line);
	rl_clear_history();
	free_list(list);
	return (0);
}
