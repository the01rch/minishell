/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:06:06 by kpires            #+#    #+#             */
/*   Updated: 2025/01/10 10:55:31 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_overwrite(t_global *g, t_cmd *cmd, char *redir)
{
	t_cmd	*cmd2;
	char	*file;

	cmd2 = cmd;
	if (cmd2->outfile > 1)
		close(cmd2->outfile);
	redir = redir + skip_spaces(redir);
	file = ft_fname(redir, 0, 0, "<>| ");
	if (!file)
		return ;
	cmd->outfile = open(file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		g->exit_val = 1;
		(perror(file), free(file));
		return ;
	}
	free(file);
	return ;
}

void	ft_append(t_global *g, t_cmd *cmd, char *redir)
{
	t_cmd	*cmd2;
	char	*file;

	cmd2 = cmd;
	if (cmd2->outfile > 1)
		close(cmd2->outfile);
	redir = redir + skip_spaces(redir);
	file = ft_fname(redir, 0, 0, "<>| ");
	if (!file)
		return ;
	cmd->outfile = open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		g->exit_val = 1;
		(perror(file), free(file));
		return ;
	}
	free(file);
	return ;
}

void	ft_redir_input(t_global *g, t_cmd *cmd, char *redir)
{
	t_cmd	*cmd2;
	char	*file;

	cmd2 = cmd;
	if (cmd2->infile > 1)
		close(cmd2->infile);
	redir = redir + skip_spaces(redir);
	file = ft_fname(redir, 0, 0, "<>| ");
	if (!file)
		return ;
	cmd->infile = open(file, O_RDONLY);
	if (cmd->infile == -1)
	{
		cmd->infile = -2;
		g->exit_val = 1;
		(perror(file), free(file));
		return ;
	}
	free(file);
	return ;
}

static int	handle_heredoc_child(t_global *g, int id, int *fd, char *redir)
{
	void	(*old_handler)(int);

	old_handler = signal(SIGINT, handl_heredoc);
	fd[2] = id;
	signal(SIGINT, handl_heredoc);
	if (check_quotes(redir, 0) > 0)
		return (ft_hd_q(g->cmds[id], fd,
				ft_fname(redir, 0, 0, "<>|"), old_handler));
	else
		return (ft_hd_nq(g, fd, ft_fname(redir, 0, 0, "<>| "), old_handler));
}

void	ft_heredoc(t_global *g, int id, char *redir)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), (void)0);
	if (pid == 0)
	{
		close(fd[0]);
		status = handle_heredoc_child(g, id, fd, redir);
		(free_cmds(g), free_list(g->lenv), exit(status));
	}
	(close(fd[1]), waitpid(pid, &status, 0));
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		g->cmds[id]->infile = -2;
		return ;
	}
	g->cmds[id]->infile = fd[0];
	return ;
}
