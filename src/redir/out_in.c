/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:06:06 by kpires            #+#    #+#             */
/*   Updated: 2024/12/19 10:15:25 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../icl/minishell.h"

static char	*ft_file_name(char *line)
{
	char	*file;
	int		i;

	i = 0;
	line = line + ft_skip_whitespaces(line);
	if (!line)
		return (NULL);
	while (line[i] && !is_in_set(line[i], "<>| "))
		i++;
	file = malloc(sizeof(char) * i + 1);
	if (!file)
		return (NULL);
	i = -1;
	while (line[i++] && !is_in_set(line[i], "<>| "))
		file[i] = line[i];
	file[i] = '\0';
	return (file);
}

int	ft_overwrite(t_command *cmd, char *line)
{
	t_command	*cmd2;
	char		*file;

	cmd2 = cmd;
	printf("ft_overwrite\n");
	if (cmd2->outfile > 1)
		close(cmd2->outfile);
	file = ft_file_name(line);
	if (!file)
		return (-1);
	printf("file:[%s]\n", file);
	cmd->outfile = open(file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		//exit value
		cmd->outfile = -2;
		printf("error ft_overwrite\n");
		free(file);
		return (-1);
	}
	free(file);
	return (1);
}

int	ft_append(t_command *cmd, char *line)
{
	t_command	*cmd2;
	char		*file;

	cmd2 = cmd;
	printf("ft_append\n");
	if (cmd2->outfile > 1)
		close(cmd2->outfile);
	file = ft_file_name(line);
	if (!file)
		return (-1);
	printf("file:[%s]\n", file);
	cmd->outfile = open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		//exit value
		cmd->outfile = -2;
		printf("error ft_append\n");
		free(file);
		return (-1);
	}
	free(file);
	return (2);
}

int	ft_redirect_input(t_command *cmd, char *line)
{
	t_command	*cmd2;
	char		*file;

	cmd2 = cmd;
	printf("ft_redirect_input\n");
	if (cmd2->infile > 1)
		close(cmd2->infile);
	file = ft_file_name(line);
	if (!file)
		return (-1);
	printf("file:[%s]\n", file);
	cmd->infile = open(file, O_RDONLY);
	if (cmd->infile == -1)
	{
		cmd->infile = -2;
		//exit value;
		printf("error ft_redirect_input\n");
		free(file);
		return (-1);
	}
	free(file);
	return (1);
}
