/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:55:25 by kpires            #+#    #+#             */
/*   Updated: 2024/12/20 23:47:26 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

void	handler_sigint(int sig)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (wait(NULL) == -1)
		rl_redisplay();
	g_signal = sig;
}

void	handler_sigquit(int sig)
{
	rl_on_new_line();
	if (wait(NULL) == -1)
	{
		printf("\e[2K\r");
		rl_redisplay();
	}
	else
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	g_signal = sig;
}
