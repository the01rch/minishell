/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:14:52 by kpires            #+#    #+#             */
/*   Updated: 2025/01/06 17:23:14 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dup_infile(t_global *g, int id)
{
	if (g->cmds[id]->infile != -1)
	{
		if (id != 0)
			close(g->cmds[id]->prev_fd);
		if (dup2(g->cmds[id]->infile, 0) == -1)
			return (1);
	}
	else if (id != 0)
	{
		if (dup2(g->cmds[id]->prev_fd, 0) == -1)
		{
			close(g->cmds[id]->prev_fd);
			return (1);
		}
		close(g->cmds[id]->prev_fd);
	}
	return (0);
}

int	dup_outfile(t_global *g, int id)
{
	if (g->cmds[id]->outfile != -1)
	{
		if (dup2(g->cmds[id]->outfile, 1) == -1)
			return (1);
	}
	else if (g->cmds[id + 1])
	{
		if (dup2(g->cmds[id]->pipe[1], 1) == -1)
			return (1);
	}
	close(g->cmds[id]->pipe[1]);
	return (0);
}

// static int	dup_inf_out_pipes(t_global *g, int id)
// {
// 	if (g->cmds[id]->infile != -1)
// 	{
// 		if (id != 0)
// 			close(g->cmds[id]->prev_fd);
// 		if (dup2(g->cmds[id]->infile, 0) == -1)
// 			return (1);
// 	}
// 	else if (id != 0)
// 	{
// 		if (dup2(g->cmds[id]->prev_fd, 0) == -1)
// 			return (close(g->cmds[id]->prev_fd), (int)1);
// 		close(g->cmds[id]->prev_fd);
// 		return (0);
// 	}
// 	if (g->cmds[id]->outfile != -1)
// 	{
// 		if (dup2(g->cmds[id]->outfile, 1) == -1)
// 			return (1);
// 	}
// 	else if (g->cmds[id + 1])
// 	{
// 		if (dup2(g->cmds[id]->pipe[1], 1) == -1)
// 			return (1);
// 	}
// 	return (close(g->cmds[id]->pipe[1]), (int)0);
// }

static void	exec_pipes(t_global *g, int id, t_env *list)
{
	if (!set_check_cmd(g, -1, id))
	{
		if (dup_infile(g, id) || dup_outfile(g, id))
		{
			(close(g->cmds[id]->pipe[1]));
			free_cmds(g);
			write(2, "exec: error with dup\n", 22);
			exit(1);
		}
		close_all_fd_child(g);
		if (gest_builtins(g, g->cmds[id]) == NONE)
			execve_cmd(g, id, list);
	}
	(free_list(list), free_cmds(g), exit(g->exit_val));
}

static void	pipe_and_fork(t_global *g, int id, t_env *list)
{
	pid_t	pid;

	if (pipe(g->cmds[id]->pipe) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		perror("Error: fork\n");
	else if (pid == 0)
	{
		close(g->cmds[id]->pipe[0]);
		exec_pipes(g, id, list);
	}
	g->last_pid = pid;
	if (g->cmds[id]->infile > 2)
		close(g->cmds[id]->infile);
	if (g->cmds[id]->outfile > 2)
		close(g->cmds[id]->outfile);
	return ;
}

void	ft_waitall(t_global *g)
{
	int	pid;
	int	exit_status;

	while (42)
	{
		pid = wait(&exit_status);
		if (pid == g->last_pid)
		{
			if (WIFEXITED(exit_status))
				g->exit_val = WEXITSTATUS(exit_status);
		}
		if (g_signal != 0)
			g->exit_val = 128 + g_signal;
		if (pid == -1)
			break ;
	}
}

void	exec_cmds(t_global *g)
{
	int		i;

	i = 0;
	while (g->cmds[i])
	{
		pipe_and_fork(g, i, g->lenv);
		close(g->cmds[i]->pipe[1]);
		if (g->cmds[i + 1])
		{
			g->cmds[i + 1]->prev_fd = g->cmds[i]->pipe[0];
			if (g->cmds[i]->prev_fd != -1)
				close(g->cmds[i]->prev_fd);
		}
		else
			break ;
		i++;
	}
	close(g->cmds[i]->pipe[0]);
	if (g->cmds[i]->prev_fd != -1)
		close(g->cmds[i]->prev_fd);
	ft_waitall(g);
}
