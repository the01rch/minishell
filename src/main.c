/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/18 19:22:23 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

bool	gest_builtins(char **arr)
{
	int	i;
	
	i = 0;
	if (ft_strncmp(arr[0], "exit", 4))
		exit(0);
	if (ft_strncmp(arr[0], "echo", 4))
	{
		i++;
		if (arr[1] && ft_strncmp(arr[1], "-n", 2))
			i++;
		while (arr[i])
			printf("%s ", arr[i++]);
		if (arr[1] && ft_strncmp(arr[1], "-n", 2))
			return (true);
		return (printf("\n"), true);
	}
	return (false);
}

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

int	main(int ac, char **av, char **env)
{
	t_env	*list;
	char	**arr;
	char	*line;

	(void)ac;
	(void)av;
	list = arr2list(env, arr_len(env));
	while (1) 
	{
		line = readline("$> ");	
		arr = str2arr(line, " ");
		gest_env(list, arr);
	}
	free_arr(arr);
	//free_list();
	return (0);
}
