/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:02:03 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/08 15:43:55 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->prev_fd = -1;
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
}

static void	fill_redir(t_global *g, t_cmd *cmd, char *line, int len)
{
	int		i;
	char	*t;
	int		k;

	k = 0;
	if (len < (int)ft_strlen(line))
	{
		cmd->redir = malloc(sizeof(char) * (ft_strlen(line) - len + 1));
		t = malloc(sizeof(char) * 1484);
		if (!cmd->redir)
			return (printf("%s", EALL), free_cmds(g), exit(1), (void)0);
		i = 0;
		while (len < (int)ft_strlen(line))
		{
			if (line[len] == 32 && !is_chr("><", line[len - 1]))
			{
				while (!is_chr("><", line[len]) && !inq(line, len, 0))
					t[k++] = line[len++];
			}
			if (len < (int)ft_strlen(line))
				cmd->redir[i++] = line[len++];
		}
		printf("t :%s\n", t);
		cmd->redir[i] = '\0';
	}
	printf("redir :%s\n", cmd->redir);
}

static void	fill_s_cmd(t_global *g, t_cmd *cmd, char *line)
{
	char	*cmd_line;
	int		i;
	char	*tmp;

	i = 0;
	while (line[i])
	{
		if (is_chr("><", line[i]) && !inq(line, i, 0))
			break ;
		i++;
	}
	init_cmd(cmd);
	fill_redir(g, cmd, line, i);
	cmd_line = malloc(sizeof(char) * (i + 1));
	if (!cmd_line)
		return (ft_perror(EALL), exit(1), (void)0);
	ft_strncpy(cmd_line, line, i);
	tmp = gest_expand(g, cmd_line);
	free(cmd_line);
	cmd->args = str2arr(tmp, " \t", true);
	free(tmp);
	if (!cmd->args)
		return (printf(EALL), free_cmds(g), exit(1), (void)0);
}

void	init_s_cmd(t_global *g, char *line)
{
	char	**arr;
	int		rows;
	int		i;

	rows = count_rows("|", line, true);
	g->cnt = rows;
	g->cmds = malloc(sizeof(t_cmd *) * (rows + 1));
	if (!g->cmds)
		return (printf("%s", EALL), exit(1), (void)0);
	arr = str2arr(line, "|", true);
	if (!arr)
		return (printf("%s", EALL), exit(1), free_cmds(g), (void)0);
	i = 0;
	while (i < rows)
	{
		g->cmds[i] = malloc(sizeof(t_cmd));
		if (!g->cmds[i])
			return (printf(EALL), (void)0);
		fill_s_cmd(g, g->cmds[i], arr[i]);
		i++;
	}
	g->cmds[i] = NULL;
	free_arr(arr);
}
