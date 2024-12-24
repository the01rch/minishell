/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:02:03 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/24 18:03:06 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	fill_redir(t_cmd *cmd, char *line, int len)
{
	int	i;

	if (len == (int)ft_strlen(line))
		cmd->redir = NULL;
	else if (len < (int)ft_strlen(line))
	{
		cmd->redir = malloc(sizeof(char) * (ft_strlen(line) - len + 1));
		if (!cmd->redir)
			return (printf("%s", EALL), exit(1), (void)0);
		i = 0;
		while (len < (int)ft_strlen(line))
			cmd->redir[i++] = line[len++];
		cmd->redir[i] = '\0';
	}
}

static void	fill_s_cmd(t_cmd *cmd, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	cmd->infile = -1;
	cmd->outfile = -1;
	while (line[i] && line[i] != '|')
	{
		if (is_chr("><", line[i]) && !inq(line, i, true))
			break ;
		i++;
	}
	fill_redir(cmd, line, i);
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (printf(EALL), exit(1), (void)0);
	ft_strncpy(tmp, line, i);
	cmd->args = str2arr(tmp, " \t", true);
	free(tmp);
	if (!cmd->args)
		return (printf(EALL), exit(1), (void)0);
}

void	init_s_cmd(t_cmd **cmd, char *line)
{
	char	**arr;
	int		rows;
	int		i;

	rows = count_rows("|", line, true);
	*cmd = malloc(sizeof(t_cmd) * rows);
	if (!*cmd)
		return (printf("%s", EALL), exit(1), (void)0);
	arr = str2arr(line, "|", true);
	if (!arr)
		return (printf("%s", EALL), exit(1), (void)0);
	i = 0;
	while (i < rows)
	{
		fill_s_cmd(cmd[i], arr[i]);
		i++;
	}
	free_arr(arr);
}
