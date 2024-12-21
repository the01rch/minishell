/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:06:06 by kpires            #+#    #+#             */
/*   Updated: 2024/12/20 22:27:52 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../icl/minishell.h"

static char	*ft_file_name(char *redir)
{
	char	*file;
	int		i;

	i = 0;
	redir = redir + ft_skip_whitespaces(redir);
	if (!redir)
		return (NULL);
	while (redir[i] && !is_chr("<>| ", redir[i]))
		i++;
	file = malloc(sizeof(char) * i + 1);
	if (!file)
		return (NULL);
	i = -1;
	while (redir[i++] && !is_chr("<>| ", redir[i]))
		file[i] = redir[i];
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

static char	*ft_getdel(t_cmd *cmd, char *redir)
{
	char	*file;

	file = ft_file_name(redir);
	printf("redir :[%s]\n", file);
	(void)cmd;
	(void)redir;
	return (NULL);
}

int	ft_heredoc(t_cmd *cmd, char *redir)
{
	char	*del;

	(void)del;
	del = ft_getdel(cmd, redir + ft_skip_whitespaces(redir));
	return (2);
}
