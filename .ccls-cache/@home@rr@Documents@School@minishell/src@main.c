/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/21 16:22:06 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_state	gest_builtins(t_env *lenv, char **arr)
{
	int	i;

	i = 0;
	if (ft_strncmp(arr[0], "exit", 4))
	{
		if (arr[1])
			return (printf("exit: too many arguments\n"), ERROR);
		printf("exit\n");
		return (free_arr(arr), free_list(lenv), exit(0), VALID);
	}
	if (ft_strncmp(arr[0], "echo", 4))
	{
		i++;
		if (arr[1] && ft_strncmp(arr[1], "-n", 2))
			i++;
		while (arr[i])
			printf("%s ", arr[i++]);
		if (arr[1] && ft_strncmp(arr[1], "-n", 2))
			return (VALID);
		return (printf("\n"), VALID);
	}
	return (gest_env(lenv, arr));
}

int	main(int ac, char **av, char **env)
{
	t_env	*list;
	char	**arr;
	char	*line;
	int		len;

	(void)ac;
	(void)av;
	len = 0;
	while (env[len])
		len++;
	list = arr2list(env, len);
	while (1)
	{
		line = readline("$> ");
		arr = str2arr(line, " ");
		if (gest_builtins(list, arr) == NONE)
			gest_shell(list, arr);
	}
	free_arr(arr);
	free_list(list);
	return (0);
}
