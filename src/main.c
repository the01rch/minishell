/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/10 18:28:26 by redrouic         ###   ########.fr       */
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

static void	listening(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO | SA_RESTART;
	act.sa_sigaction = (void *)ft_handler;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

int	main(int ac, char **av, char **env)
{
	t_env	*list;
	char	**arr;
	char	*line;

	list = arr2list(env);
	listening();
	while (ac && av)
	{
		line = readline("$> ");
		if (!line)
			break ;
		add_history(line);
		arr = str2arr(line, " ", true);
		for (int i = 0; arr[i]; i++)
		{
			arr[i] = ft_strdup(gest_sign(list, arr[i]));
			printf("arr[%d] :%s\n", i, arr[i]);
		}
		if (gest_builtins(list, arr) == NONE)
			gest_shell(list, arr);
	}
	rl_clear_history();
	return (free_list(list), 0);
}
