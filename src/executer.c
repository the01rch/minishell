/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:34:17 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/21 12:35:34 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

static char	*check_access(t_env *lenv, char **arr)
{
	char	**tab;
	char	*path;
	char	*full_path;
	char	*path_str;
	char	**tab_start;

	path_str = plist(lenv, "PATH");
	if (!path_str)
		return (NULL);
	tab = str2arr(path_str, ":", false);
	free(path_str);
	if (!tab)
		return (NULL);
	tab_start = tab;
	while (*tab)
	{
		full_path = pwrapper(*tab, arr[0], '/');
		if (!full_path)
			return (free_arr(tab_start), NULL);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			path = ft_strdup(full_path);
			free(full_path);
			if (!path)
				return (free_arr(tab_start), exit(0), path);
			return (free_arr(tab_start), path);
		}
		free(full_path);
		tab++;
	}
	return (free_arr(tab_start), NULL);
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

void	gest_shell(t_env *lenv, t_cmd *cmd)
{
	char	*path;
	pid_t	pid;

	path = check_access(lenv, cmd->args);
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), exit(0), (void)0);
	else if (pid == 0)
	{
		if (!path)
		{
			printf("%s: Command not found.\n", cmd->args[0]);
			exit(0);
		}
		execve(path, cmd->args, list2arr(lenv));
	}
	if (pid > 0)
		wait(NULL);
	free(path);
}
