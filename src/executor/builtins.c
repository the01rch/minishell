/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:30:48 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/11 13:11:11 by kpires           ###   ########.fr       */
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
	char	*pl;

	if (!arr[1])
	{
		pl = plist(g->lenv, "HOME");
		(chdir(pl), free(pl));
		tmp = pwrapper("OLDPWD", plist(g->lenv, "PWD"), '=');
		(ft_export(g, &tmp, false), free(tmp));
		tmp = pwrapper("PWD", plist(g->lenv, "HOME"), '=');
		return (ft_export(g, &tmp, false), free(tmp), true);
	}
	else if (arr[2])
		return (g->exit_val = 1, ft_perror(" too many arguments", true), false);
	else if (chdir(arr[1]) == -1)
		return (g->exit_val = 1, perror("cd"), false);
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		tmp = pwrapper("OLDPWD", plist(g->lenv, "PWD"), '=');
		(ft_export(g, &tmp, false), free(tmp));
		tmp = pwrapper("PWD", cwd, '=');
		return (ft_export(g, &tmp, false), free(tmp), true);
	}
	return (perror("getcwd"), true);
}

static t_state	ft_echo(t_global *g, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n"))
		i++;
	while (cmd->args[i] != NULL)
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n"))
		return (g->exit_val = 0, VALID);
	return (write(1, "\n", 1), g->exit_val = 0, VALID);
}

static t_state	gest_env(t_global *g, char **arr)
{
	char	*result;

	if (ft_strcmp(arr[0], "env"))
	{
		if (arr[1])
		{
			(ft_perror("env: '", false), ft_perror(arr[1], false));
			ft_perror("': No such file or directory\n", false);
			return (g->exit_val = 1, ERROR);
		}
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
	if (ft_strcmp(arr[0], "cd"))
		return (ft_cd(g, arr), VALID);
	return (NONE);
}

t_state	gest_builtins(t_global *g, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd->args[0], "export"))
	{
		while (cmd->args[i])
			i++;
		if (i > 1)
			return (ft_export(g, &cmd->args[1], true), VALID);
		return (ft_export(g, &cmd->args[1], false), VALID);
	}
	i = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = remq(cmd->args[i]);
		i++;
	}
	i = 0;
	if (ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(g, cmd, true));
	if (ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(g, cmd));
	return (gest_env(g, cmd->args));
}
