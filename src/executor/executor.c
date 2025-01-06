/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:34:17 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/06 17:23:05 by kpires           ###   ########.fr       */
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

void	execve_absolute_path(t_global *g, int id, t_env *lenv)
{
	if (execve(g->cmds[id]->args[0], g->cmds[id]->args, list2arr(lenv)) == -1)
	{
		if (access(g->cmds[id]->args[0], F_OK) == 0)
		{
			write(2, g->cmds[id]->args[0], ft_strlen(g->cmds[id]->args[0]));
			if (access(g->cmds[id]->args[0], X_OK) != 0)
				write(2, ": Permission denied\n", 20);
			else
				write(2, ": Is a directory\n", 17);
			free_cmds(g);
			exit(126);
		}
		else
			perror(g->cmds[id]->args[0]);
		free_cmds(g);
		exit(127);
	}
}

void	execve_cmd_path(t_global *g, int id, t_env *lenv)
{
	char	*path;

	path = check_access(lenv, g->cmds[id]->args);
	if (!path)
	{
		write(2, g->cmds[id]->args[0], ft_strlen(g->cmds[id]->args[0]));
		write(2, ": command not found\n", 20);
		free_list(lenv);
		free_cmds(g);
		exit(127);
	}
	if (execve(path, g->cmds[id]->args, list2arr(lenv)) == -1)
	{
		perror("execve");
		free_list(lenv);
		free(path);
		free_cmds(g);
		exit(1);
	}
}

/*
	if (g->cmds[id]->args[0][0] == '\0')
	{
		i = 0;
		free(g->cmds[id]->args[0]);
		while (g->cmds[id]->args[i + 1])
		{
			g->cmds[id]->args[i] = g->cmds[id]->args[i + 1];
			i++;
		}
		g->cmds[id]->args[i] = NULL;
		if (g->cmds[id]->args[0])
		{
			i = 0;
			while (g->cmds[id]->args[0][i])
			{
				if (g->cmds[id]->args[0][i] == '/')
				{
					execve_absolute_path(g, id, lenv);
					return ;
				}
				i++;
			}
			execve_cmd_path(g, id, lenv);
		}
		return ;
	}
*/

void	execve_cmd(t_global *g, int id, t_env *lenv)
{
	int		i;

	if (g->cmds[id] == NULL)
	{
		if (g->cmds[id + 1])
			execve_cmd(g, id + 1, lenv);
		return ;
	}
	i = 0;
	while (g->cmds[id]->args[0][i])
	{
		if (g->cmds[id]->args[0][i] == '/')
		{
			execve_absolute_path(g, id, lenv);
			return ;
		}
		i++;
	}
	execve_cmd_path(g, id, lenv);
}
