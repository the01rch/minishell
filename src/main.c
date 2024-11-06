/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/06 16:27:53 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

void gest_builtin(char *line)
{
	if (ft_strcmp(line, "exit"))
	{
		free(line);
		exit(0);
	}
	if (ft_strcmp(line, "echo"))
	{
		ft_putstr(line);
		ft_putchar('\n');
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line;

	while (1) {
		line = readline("$> ");	
		gest_builtin(line);
	}
	return (0);
}
