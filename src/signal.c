/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:55:25 by kpires            #+#    #+#             */
/*   Updated: 2024/12/13 16:02:04 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

static void	ft_handler(int sig, siginfo_t *info, void *context)
{
	if (info->si_signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ((void)context, (void)sig, (void)0);
}

void	listening(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO | SA_RESTART;
	act.sa_sigaction = (void *)ft_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
