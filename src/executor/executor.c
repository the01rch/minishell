/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:34:17 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/30 15:42:41 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*check_access(t_env *lenv, char **arr)
{
	char	**tab;
	char	*path;
	int		i;

	i = 0;
	path = plist(lenv, "PATH");
	if (!path)
		return (NULL);
	tab = str2arr(path, ":", false);
	free(path);
	if (!tab)
		return (NULL);
	path = NULL;
	while (tab[i] != NULL)
	{
		path = pwrapper(tab[i++], arr[0], '/');
		if (!path)
			return (free_arr(tab), NULL);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (free_arr(tab), path);
		free(path);
		path = NULL;
	}
	return (free_arr(tab), NULL);
}

char	**list2arr(t_env *lenv)
{
	t_env	*tmp;
	char	**arr;
	int		i;

	i = 0;
	tmp = lenv;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (tmp)
	{
		arr[i++] = pwrapper(tmp->name, tmp->content, '=');
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	gest_shell(t_env *lenv, t_cmd *cmd, int *std_save)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	path = check_access(lenv, cmd->args);
	if (pid < 0)
		return (perror("Error :Fork failed\n"), exit(0), (void)0);
	else if (pid == 0)
	{
		if (cmd->infile != -1)
			(close(std_save[0]), close(cmd->infile));
		if (cmd->outfile != -1)
			(close(std_save[1]), close(cmd->outfile));
		if (!path)
		{
			printf("%s: Command not found.\n", cmd->args[0]);
			(free_list(lenv));
			exit(0);
		}
		execve(path, cmd->args, list2arr(lenv));
	}
	if (pid > 0)
		wait(NULL);
	free(path);
}
