/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/17 02:15:41 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

bool	gest_env(char **arr, char **env)
{
	char	cwd[1024];

	if (ft_strncmp(arr[0], "pwd", 3))
		return (printf("%s\n", getenv("PWD")), true);
	if (ft_strncmp(arr[0], "env", 3))
	{
		while (*env)
			printf("%s\n", *env++);
		return (true);
	}
	if (ft_strncmp(arr[0], "cd", 2))
	{
		if (!arr[1])
			return (chdir(getenv("HOME")), true);
		if (chdir(arr[1]) == -1)
			return (perror("cd"), false);
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_setenv("PWD", cwd, 1);
		else
			perror("getcwd");
		return (true);
	}
	return (false);
}

bool	gest_builtins(char **arr, char **env)
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
	return (gest_env(arr, env));
}

void	free_arr(char **arr)
{
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(arr);
}

char **copy_env(char **env)
{
	char	**copy;
	int		len;

	len = 0;
	while (env[len])
		len++;
	copy = malloc(sizeof(char *) * len + 1);
	if (!copy)
		return (NULL);
	len = 0;
	while (*env)
	{
		copy[len++] = ft_strdup(*env);
		env++;
	}
	copy[len] = NULL;
	return (copy);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**arr;
	char	**copy;

	(void)ac;
	(void)av;
	copy = copy_env(env);
	while (1) 
	{
		line = readline("$> ");	
		arr = str2arr(line, " ");
		gest_builtins(arr, copy);
	}
	free_arr(arr);
	free_arr(copy);
	return (0);
}
