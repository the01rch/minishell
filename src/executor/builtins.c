/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:30:48 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/09 23:10:33 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_unset(t_global *g, char *str)
{
	t_env	*tmp;
	t_env	*to_delete;

	if (!g->lenv || !str)
		return ;
	g->exit_val = 0;
	if (ft_strcmp(str, g->lenv->name))
	{
		to_delete = g->lenv;
		g->lenv = g->lenv->next;
		free_node(to_delete);
		return ;
	}
	tmp = g->lenv;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(str, tmp->next->name))
		{
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			free_node(to_delete);
			return ;
		}
		tmp = tmp->next;
	}
}

static bool	ft_cd(t_global *g, char **arr)
{
	char	cwd[1024];
	char	*tmp;

	if (!arr[1])
	{
		chdir(plist(g->lenv, "HOME"));
		tmp = pwrapper("PWD", plist(g->lenv, "HOME"), '=');
		ft_export(g, &tmp);
		return (free(tmp), true);
	}
	if (arr[2])
		return (g->exit_val = 1, ft_perror(" too many arguments\n"), false);
	if (chdir(arr[1]) == -1)
		return (g->exit_val = 1, perror("cd"), false);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		tmp = pwrapper("PWD", cwd, '=');
		return (ft_export(g, &tmp), free(tmp), true);
	}
	return (perror("getcwd"), true);
}

static t_state	gest_env(t_global *g, char **arr)
{
	char	*result;

	if (ft_strcmp(arr[0], "env"))
	{
		if (arr[1])
			return (g->exit_val = 1, printf(EENV, arr[1]), ERROR);
		return (plist(g->lenv, NULL), VALID);
	}
	if (ft_strcmp(arr[0], "pwd"))
	{
		result = plist(g->lenv, "PWD");
		if (result)
			return (printf("%s\n", result), free(result), VALID);
		g->exit_val = 1;
		return (ERROR);
	}
	if (ft_strcmp(arr[0], "unset"))
		return (ft_unset(g, arr[1]), VALID);
	if (ft_strcmp(arr[0], "export"))
		return (ft_export(g, &arr[1]), VALID);
	if (ft_strcmp(arr[0], "cd"))
		return (ft_cd(g, arr), VALID);
	return (NONE);
}

t_state	gest_builtins(t_global *g, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd->args[0], "echo"))
	{
		i++;
		if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n"))
			i++;
		while (cmd->args[i] != NULL)
		{
			if (cmd->args[i + 1] != NULL)
				printf("%s ", cmd->args[i++]);
			else
				printf("%s", cmd->args[i++]);
		}
		if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n"))
			return (g->exit_val = 0, VALID);
		return (printf("\n"), g->exit_val = 0, VALID);
	}
	return (gest_env(g, cmd->args));
}
