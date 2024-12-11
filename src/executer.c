/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:34:17 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/05 07:53:53 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

char	*check_access(t_env *lenv, char **arr)
{
	char	**tab;
	int		i;	

	tab = str2arr(plist(lenv, "PATH"), ":", false);
	i = 0;
	if (!tab)
		return (NULL);
	while (i < 7)
	{
		if (access(pwrapper(tab[i], arr[0], '/'), F_OK) == 0
			&& access(pwrapper(tab[i], arr[0], '/'), X_OK) == 0)
			return (pwrapper(tab[i], arr[0], '/'));
		i++;
	}
	return (NULL);
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
		arr[i] = pwrapper(tmp->name, tmp->content, '=');
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	gest_shell(t_env *lenv, char **arr)
{
	char	*path;
	pid_t	pid;

	path = check_access(lenv, arr);
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), exit(0), (void)0);
	else if (pid == 0)
	{
		if (!path)
		{
			printf("%s: Command not found.\n", arr[0]);
			exit(0);
		}
		execve(path, arr, list2arr(lenv));
	}
	if (pid > 0)
		wait(NULL);
}
