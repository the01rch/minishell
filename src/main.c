/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/06 22:07:16 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"


void	free_arr(char **arr)
{
	int i =0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


void gest_builtin(char *line, char **env)
{
	char	**arr;
	int i = 0;

	if (ft_strncmp(line, "exit", 4))
		exit(0);
	if (ft_strncmp(line, "echo", 4))
	{
		arr = str2arr(line);
		i++;
		while (arr[i])
		{
			printf("%s ", arr[i]);
			i++;
		}
		printf("\n");
		free_arr(arr);
	}
	
	if (ft_strncmp(line, "env", 3))
	{
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	}
//	free_arr(arr);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line;

	if(ac != 1)
	{
		printf("Unvalid argument \n");
		exit(0);
	}
	while (1) 
	{
		line = readline("$> ");
		gest_builtin(line, env);
		if (!line)
			break;
	}
	free(line);
	return (0);
}
