/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:06:06 by kpires            #+#    #+#             */
/*   Updated: 2024/12/24 01:30:11 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_fname(char *redir, int i, int len, char *dels)
{
	char	*file;

	if (!redir)
		return (NULL);
	while (redir[i] && !is_chr(dels, redir[i]))
		i++;
	file = malloc(sizeof(char) * (i + 1));
	if (!file)
		return (NULL);
	i = 0;
	while (redir[i] && !is_chr(dels, redir[i]))
	{
		if (redir[i] == '"')
		{
			i++;
			continue ;
		}
		file[len++] = redir[i++];
	}
	file[len] = '\0';
	return (file);
}

/*SET EXIT VALUE -> if (cmd->outfile == -1){}*/
int	ft_overwrite(t_cmd *cmd, char *redir)
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
		perror(file);
		free(file);
		return (-1);
	}
	free(file);
	return (1);
}

/*SET EXIT VALUE -> if (cmd->outfile == -1){}*/
int	ft_append(t_cmd *cmd, char *redir)
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
		perror(file);
		free(file);
		return (-1);
	}
	free(file);
	return (2);
}

/*SET EXIT VALUE -> if (cmd->outfile == -1){}*/
int	ft_redirect_input(t_cmd *cmd, char *redir)
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
		perror(file);
		free(file);
		return (-1);
	}
	free(file);
	return (1);
}

int	ft_heredoc(t_cmd *cmd, char *redir, t_env *lenv)
{
	int		fd[2];
	int		i;
	int		skip;

	redir = redir + skip_spaces(redir);
	i = 0;
	skip = 0;
	while (redir[i])
	{
		if (ft_strncmp(redir + i, "<<", 2) == 0)
			skip = i + 2 + skip_spaces(redir + i + 2);
		i++;
	}
	redir = redir + skip;
	if (skip == 0)
		skip = 2;
	if (pipe(fd) == -1)
		return (-1);
	if (check_quotes(redir, 0) || *redir == '\\')
		return (skip + ft_hd_q(cmd, fd, ft_fname(redir, 0, 0, "<>|")));
	else
		return (skip + ft_hd_nq(cmd, fd, ft_fname(redir, 0, 0, "<>| "), lenv));
}
