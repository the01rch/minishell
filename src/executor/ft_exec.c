/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:30:38 by kpires            #+#    #+#             */
/*   Updated: 2024/12/23 14:21:35 by redrouic         ###   ########.fr       */
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

void	close_all_fd_child(t_cmd *cmd)
{
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
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
		close_all_fd_child(cmd);
		if (i != 0)
			close(cmd->prev_fd);
		close(cmd->pipe[1]);
	}
	return (1);
}

static int	exec_cmd(t_cmd *cmd, t_env *list)
{
	int		std_save[2];

	if (set_check_cmd(cmd, list, -1))
		return (1);
	if (dup_inf_out(cmd, std_save) == 1)
	{
		printf("exec: error with dup\n");
		//exit value;
		return (1);
	}
	if (gest_builtins(list, cmd) == NONE)
		gest_shell(list, cmd, std_save);
	close_fd(cmd, std_save, false);
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
