/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:20:05 by kpires            #+#    #+#             */
/*   Updated: 2025/01/03 00:17:07 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	close_fd(t_global *g, t_env *list, int *std_save, bool is_error)
{
	if (g->cmds[std_save[2]]->infile != -1)
	{
		if (dup2(std_save[0], 0) == -1 || is_error)
		{
			close(std_save[0]);
			if (g->cmds[std_save[2]]->outfile != -1)
				close(std_save[1]);
			if (is_error)
				(close_all_fd_child(g), free_cmds(g), free_list(list), exit(1));
		}
		close(std_save[0]);
	}
	if (g->cmds[std_save[2]]->outfile != -1)
	{
		if (dup2(std_save[1], 1) == -1 || is_error)
		{
			close(std_save[1]);
			if (is_error)
				(close_all_fd_child(g), free_cmds(g), free_list(list), exit(1));
		}
		close(std_save[1]);
	}
	return (1);
}

static int	dup_inf_out(t_global *g, t_env *list, int *std_save)
{
	if (g->cmds[std_save[2]]->infile != -1)
	{
		std_save[0] = dup(0);
		if (std_save[0] == -1)
			return (1);
		if (dup2(g->cmds[std_save[2]]->infile, 0) == -1)
		{
			close(std_save[0]);
			return (1);
		}
	}
	if (g->cmds[std_save[2]]->outfile != -1)
	{
		std_save[1] = dup(1);
		if (std_save[1] == -1)
			return (close_fd(g, list, std_save, true));
		if (dup2(g->cmds[std_save[2]]->outfile, 1) == -1)
			return (close_fd(g, list, std_save, true));
	}
	return (0);
}

static void	gest_shell(t_global *g, t_env *lenv, int id, int *std_save)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("Error :Fork failed\n"), free_cmds(g),
			free_list(lenv), exit(0), (void)0);
	else if (pid == 0)
	{
		if (g->cmds[id]->infile != -1)
			(close(std_save[0]), close(g->cmds[id]->infile));
		if (g->cmds[id]->outfile != -1)
			(close(std_save[1]), close(g->cmds[id]->outfile));
		execve_cmd(g, id, lenv);
	}
	g->last_pid = pid;
	ft_waitall(g);
}

int	exec_cmd(t_global *g, int id, t_env *list)
{
	int		std_save[3];

	if (set_check_cmd(g, -1, 0, list))
		return (1);
	if (ft_strcmp(g->cmds[id]->args[0], "exit"))
		return (ft_exit(g, g->cmds[id], true, list));
	std_save[2] = id;
	if (dup_inf_out(g, list, std_save) == 1)
	{
		printf("exec: error with dup\n");
		g->exit_val = 1;
		return (g->exit_val);
	}
	if (gest_builtins(list, g->cmds[id]) == NONE)
		gest_shell(g, list, id, std_save);
	close_fd(g, list, std_save, false);
	return (g->exit_val);
}
