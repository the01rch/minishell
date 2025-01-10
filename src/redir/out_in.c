/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:06:06 by kpires            #+#    #+#             */
/*   Updated: 2025/01/10 15:14:55 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_overwrite(t_global *g, t_cmd *cmd, char *redir)
{
	t_cmd	*cmd2;
	char	*file;

	cmd2 = cmd;
	if (cmd2->outfile > 1)
		close(cmd2->outfile);
	redir = redir + skip_spaces(redir);
	file = ft_fname(redir, 0, 0, "<>| ");
	if (!file)
		return (-1);
	cmd->outfile = open(file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		g->exit_val = 1;
		(perror(file), free(file));
		return (-1);
	}
	free(file);
	return (1);
}

int	ft_append(t_global *g, t_cmd *cmd, char *redir)
{
	t_cmd	*cmd2;
	char	*file;

	cmd2 = cmd;
	if (cmd2->outfile > 1)
		close(cmd2->outfile);
	redir = redir + skip_spaces(redir);
	file = ft_fname(redir, 0, 0, "<>| ");
	if (!file)
		return (-1);
	cmd->outfile = open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		g->exit_val = 1;
		(perror(file), free(file));
		return (-1);
	}
	free(file);
	return (2);
}

int	ft_redir_input(t_global *g, t_cmd *cmd, char *redir)
{
	t_cmd	*cmd2;
	char	*file;

	cmd2 = cmd;
	if (cmd2->infile > 1)
		close(cmd2->infile);
	redir = redir + skip_spaces(redir);
	file = ft_fname(redir, 0, 0, "<>| ");
	if (!file)
		return (-1);
	cmd->infile = open(file, O_RDONLY);
	if (cmd->infile == -1)
	{
		cmd->infile = -2;
		g->exit_val = 1;
		(perror(file), free(file));
		return (-1);
	}
	free(file);
	return (1);
}

static int	handle_heredoc_child(t_global *g, int id, int *fd, char *redir)
{
	int		i;
	void	(*old_handler)(int);
	int		k;

	old_handler = signal(SIGINT, handl_heredoc);
	i = skip_spaces(redir + 0);
	fd[2] = id;
	signal(SIGINT, handl_heredoc);
	k = 0;
	while (!is_chr("<>|", redir[k]))
		k++;
	if (k == 0)
		k = 2;
	// printf("str + i: [%s]\n", redir + i);
	// printf("str + i + at: [%s]\n", redir + i + (k - 1));
	// printf("inq(redir + i - 1, i + (k - 2)); = %d\n", inq(redir + i, (k - 3), '\0'));
	if (inq(redir + i, (k - 3), '\0'))
		return ((i) + ft_hd_q(g->cmds[id], fd
				, ft_fname(redir + i, 0, 0, "<>|"), old_handler));
	else
		return ((i)
			+ ft_hd_nq(g, fd, ft_fname(redir + i, 0, 0, "<>| "), old_handler));
}

int	ft_heredoc(t_global *g, int id, char *redir)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), -1);
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
		return (-1);
	}
	g->cmds[id]->infile = fd[0];
	return (2);
}
