/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:06:06 by kpires            #+#    #+#             */
/*   Updated: 2024/12/23 06:53:25 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_file_name(char *redir)
{
	char	*file;
	int		i;

	i = 0;
	if (!redir)
		return (NULL);
	redir += skip_spaces(redir);
	while (redir[i] && !is_chr("<>| ", redir[i]))
		i++;
	file = malloc(sizeof(char) * (i + 1));
	if (!file || !redir)
		return (NULL);
	i = 0;
	while (redir[i] && !is_chr("<>| ", redir[i]))
	{
		file[i] = redir[i];
		i++;
	}
	file[i] = '\0';
	return (file);
}

/*SET EXIT VALUE -> if (cmd->outfile == -1){}*/
int	ft_overwrite(t_cmd *cmd, char *redir)
{
	t_cmd	*cmd2;
	char	*file;

	cmd2 = cmd;
	printf("ft_overwrite\n");
	if (cmd2->outfile > 1)
		close(cmd2->outfile);
	file = ft_file_name(redir);
	if (!file)
		return (-1);
	printf("file:[%s]\n", file);
	cmd->outfile = open(file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		printf("error ft_overwrite\n");
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
	printf("ft_append\n");
	if (cmd2->outfile > 1)
		close(cmd2->outfile);
	file = ft_file_name(redir);
	if (!file)
		return (-1);
	printf("file:[%s]\n", file);
	cmd->outfile = open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		printf("error ft_append\n");
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
	printf("ft_redirect_input\n");
	if (cmd2->infile > 1)
		close(cmd2->infile);
	file = ft_file_name(redir);
	if (!file)
		return (-1);
	printf("file:[%s]\n", file);
	cmd->infile = open(file, O_RDONLY);
	if (cmd->infile == -1)
	{
		cmd->infile = -2;
		printf("error ft_redirect_input\n");
		free(file);
		return (-1);
	}
	free(file);
	return (1);
}

int	ft_heredoc(t_cmd *cmd, char *redir, t_env *lenv)
{
	char	*del;
	int		fd[2];

	redir += skip_spaces(redir);
	del = ft_file_name(redir);
	if (ft_strlen(del) < ft_strlen(redir))
		printf("dif:%d\n", (ft_strlen(redir) - ft_strlen(del)));
	if (pipe(fd) == -1)
		return (free(del), -1);
	if (inq(del, ft_strlen(del), DQUOTE))
		printf("in doule quotes \n");
	else if (inq(del, ft_strlen(del), SQUOTE))
		printf("in single quotes \n");
	else
		return (ft_here_nquote(cmd, fd, del, lenv));
	return (2 + ft_strlen(del));
}
