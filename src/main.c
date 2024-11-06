/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/06 15:57:35 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str++);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line;

	while (1) {
		line = readline("$> ");	
		ft_putstr(line);
	}
	return (0);
}
