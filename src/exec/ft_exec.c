/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:30:38 by kpires            #+#    #+#             */
/*   Updated: 2024/12/21 12:36:36 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../icl/minishell.h"

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
		if (ft_export(list, v_))
		{
			result = plist(list, "_");
			printf("✅[UPDATED]$_=%s\n", result);
		}
	}
	free(v_);
}

static int	set_check_cmd(t_cmd *cmd, t_env *list, int i)
{
	(void)list;
	//set $_ at last path cmd running
	if (cmd && cmd->args && cmd->args[0])
	{
		update_last_cmd(cmd, list);
		if (cmd->infile != -2 && cmd->outfile != -2)
			return (0);
	}
	//multiple pipes gest
	if (i != -1)
	{
		//close all child
		if (i != 0)
			close(cmd->prev_fd);
		close(cmd->pipe[1]);
	}
	return (1);
}

static int	exec_cmd(t_cmd *cmd, t_env *list)
{
	if (set_check_cmd(cmd, list, -1))
		return (1);
	if (gest_builtins(list, cmd) == NONE)
		gest_shell(list, cmd);
	return (0);
}

int	ft_exec(t_cmd cmd, t_env *list)
{
	int		cmd_count;

	cmd_count = 1;
	g_signal = 0;
	if (cmd_count == 1)
		return (exec_cmd(&cmd, list));
	return (0);
}
