/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:30:38 by kpires            #+#    #+#             */
/*   Updated: 2025/01/11 13:12:21 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	update_last_cmd(t_global *g, t_cmd *cmd)
{
	char	*v_;
	int		len;
	char	*result;

	len = (11 + ft_strlen(cmd->args[0]) + 1);
	v_ = malloc(sizeof(char) * len);
	if (!v_)
	{
		ft_perror("env: error with mallocc \n", false);
		return ;
	}
	ft_strncpy(v_, "_=/usr/bin/", 12);
	ft_strlcat(v_, cmd->args[0], len);
	result = plist(g->lenv, "_");
	if (result)
	{
		ft_export(g, &v_, false);
		free(result);
	}
	free(v_);
}

void	close_all_fd_child(t_global *g)
{
	int	i;

	i = 0;
	while (g->cmds[i])
	{
		if (g->cmds[i]->infile > 2)
			close(g->cmds[i]->infile);
		if (g->cmds[i]->outfile > 2)
			close(g->cmds[i]->outfile);
		i++;
	}
}

int	set_check_cmd(t_global *g, int id)
{
	if (g->cmds[id] && g->cmds[id]->args && g->cmds[id]->args[0]
		&& ft_strlen(g->cmds[id]->args[0]) != 0)
	{
		if (ft_strcmp(g->cmds[0]->args[0], "exit"))
			return (0);
		update_last_cmd(g, g->cmds[id]);
		if (g->cmds[id]->infile != -2 && g->cmds[id]->outfile != -2)
			return (0);
	}
	if (g->cnt > 1)
	{
		close_all_fd_child(g);
		if (id != 0)
			close(g->cmds[id]->prev_fd);
		close(g->cmds[id]->pipe[1]);
	}
	return (1);
}

int	ft_exec(t_global *g)
{
	g_signal = 0;
	if (!g->cnt)
		return (0);
	if (g->cnt == 1)
		return (exec_cmd(g, 0));
	else
		exec_cmds(g);
	return (0);
}
