/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/16 03:36:50 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

/*
void	free_arr(char **arr)
{
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(arr);
}
*/

void	gest_env(char *line, char **env)
{
	int i;
	
	i = 0;
	if (ft_strncmp(line, "env", 3))
	{
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	}
	if (ft_strncmp(line, "pwd", 3))
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], "PWD", 3))
				printf("%s\n", &env[i][4]);
			i++;
		}
	}
}

void gest_builtin(char *line, char **env)
{
	char	**arr;

	arr = str2arr(line, " ");
	if (ft_strncmp(line, "exit", 4))
		exit(0);
	if (ft_strncmp(line, "echo", 4))
	{
		arr++;
		while (*arr)
		{
			printf("%s ", *arr);
			arr++;
		}
		printf("\n");
	}
	gest_env(line, env);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	while (1) 
	{
		line = readline("$> ");	
		gest_builtin(line, env);
	}
	return (0);
}
