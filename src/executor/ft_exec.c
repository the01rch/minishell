/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:30:38 by kpires            #+#    #+#             */
/*   Updated: 2025/01/03 00:17:10 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit(t_global *g, t_cmd *cmd, bool print, t_env *lenv)
{
	int	nb;

	if (print)
		printf("exit\n");
	if (!cmd->args[1] || cmd->args[1] == NULL)
		(close_all_fd_child(g), free_cmds(g),
			free_list(lenv), exit(g->exit_val));
	if ((ft_is_nb(cmd->args[1]) || ft_strlen(cmd->args[1]) >= 19)
		&& ft_strncmp("9223372036854775807", cmd->args[1], 19) < 0)
	{
		write(2, "exit: ", 6);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": numeric argument required\n", 28);
		close_all_fd_child(g);
		(free_cmds(g), free_list(lenv), exit(2));
	}
	if (ft_is_nb(cmd->args[1]) == 0 && cmd->args[1] && cmd->args[2] == NULL)
	{
		nb = ft_atoi(cmd->args[1]);
		close_all_fd_child(g);
		(free_cmds(g), free_list(lenv), exit(nb % 256));
	}
	write(2, "exit: too many arguments\n", 25);
	g->exit_val = 1;
	return (1);
}

static void	update_last_cmd(t_cmd *cmd, t_env *list)
{
	char	*v_;
	int		len;
	char	*result;

	len = (11 + ft_strlen(cmd->args[0]) + 1);
	v_ = malloc(sizeof(char) * len);
	if (!v_)
	{
		printf("env: error with mallocc \n");
		return ;
	}
	ft_strncpy(v_, "_=/usr/bin/", 12);
	ft_strlcat(v_, cmd->args[0], len);
	result = plist(list, "_");
	if (result)
	{
		ft_export(list, v_);
		free(result);
	}
	free(v_);
}

void	close_all_fd_child(t_global *g)
{
	int	i;

	i = 0;
	while (i < g->cnt)
	{
		if (g->cmds[i]->infile > 2)
			close(g->cmds[i]->infile);
		if (g->cmds[i]->outfile > 2)
			close(g->cmds[i]->outfile);
		i++;
	}
}

int	set_check_cmd(t_global *g, int i, int c, t_env *list)
{
	if (g->cmds[c] && g->cmds[c]->args && g->cmds[c]->args[0])
	{
		if (ft_strcmp(g->cmds[0]->args[0], "exit"))
			return (0);
		update_last_cmd(g->cmds[c], list);
		if (g->cmds[c]->infile != -2 && g->cmds[c]->outfile != -2)
			return (0);
	}
	if (i != -1)
	{
		close_all_fd_child(g);
		if (i != 0)
			close(g->cmds[c]->prev_fd);
		close(g->cmds[c]->pipe[1]);
	}
	return (1);
}

int	ft_exec(t_global *g, t_env *list)
{
	g_signal = 0;
	if (!g->cnt)
		return (0);
	if (g->cnt == 1)
		return (exec_cmd(g, 0, list));
	else
		exec_cmds(g, list);
	return (0);
}
