/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:30:38 by kpires            #+#    #+#             */
/*   Updated: 2025/01/01 18:31:32 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static int	set_check_cmd(t_global *g, int i, int c, t_env *list)
{
	if (g->cmds && g->cmds[c].args && g->cmds[c].args[0])
	{
		update_last_cmd(&g->cmds[c], list);
		if (g->cmds[c].infile != -2 && g->cmds[c].outfile != -2)
			return (0);
	}
	if (i != -1)
	{
		close_all_fd_child(g);
		if (i != 0)
			close(g->cmds[c].prev_fd);
		close(g->cmds[c].pipe[1]);
	}
	return (1);
}

/* if (dup_inf_out(cmd, std_save) == 1) exit value in struct*/
static int	exec_cmd(t_global *g, t_env *list)
{
	int		std_save[2];

	if (set_check_cmd(g, -1, 0, list))
		return (1);
	if (ft_strcmp(g->cmds->args[0], "exit"))
	{
		if (g->cmds->args[1])
			return (printf("exit: too many arguments\n"), ERROR);
		(printf("exit\n"), free_list(list), free_cmds(g), exit(1));
	}
	if (dup_inf_out(g->cmds, std_save) == 1)
	{
		printf("exec: error with dup\n");
		g->exit_val = 1;
		return (g->exit_val);
	}
	if (gest_builtins(list, g->cmds) == NONE)
		gest_shell(list, g->cmds, std_save);
	close_fd(g->cmds, std_save, false);
	return (g->exit_val);
}

void	exec_cmds(t_global *g, t_env *list)
{
	(void)list;
	(void)g;
}

int	ft_exec(t_global *g, t_env *list)
{
	g_signal = 0;
	if (!g->cnt)
		return (0);
	if (g->cnt == 1)
		return (exec_cmd(g, list));
	else
		exec_cmds(g, list);
	return (0);
}
