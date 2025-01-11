/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:02:03 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/11 14:42:13 by kpires           ###   ########.fr       */
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

static void	concat_quoted_string(char *dest, char *line, int *i, int *j)
{
	char	quote_char;
	int		len;

	len = ft_strlen(line);
	while (*j < len)
	{
		if (line[*j] == '"' || line[*j] == '\'')
		{
			quote_char = line[*j];
			dest[(*i)++] = line[(*j)++];
			while (*j < len && line[*j] != quote_char)
				dest[(*i)++] = line[(*j)++];
			if (*j < len)
				dest[(*i)++] = line[(*j)++];
		}
		else if (!is_chr(" \t><", line[*j]))
			dest[(*i)++] = line[(*j)++];
		else
			break ;
	}
}

static int	fill_redir(t_global *g, t_cmd *cmd, char *line, int len)
{
	int		i[2];

	if (len < (int)ft_strlen(line))
	{
		cmd->redir = malloc(sizeof(char) * (ft_strlen(line) - len + 2));
		if (!cmd->redir)
			return (ft_perror(EALL, false), free_cmds(g), exit(1), (int)len);
		i[0] = 0;
		i[1] = len;
		while (i[1] < (int)ft_strlen(line))
		{
			if (is_chr("><", line[i[1]]))
			{
				while (i[1] < ft_strlen(line) && (is_chr("><", line[i[1]])
						|| is_chr(" \t", line[i[1]])))
					cmd->redir[i[0]++] = line[i[1]++];
				concat_quoted_string(cmd->redir, line, &i[0], &i[1]);
				cmd->redir[i[0]++] = ' ';
			}
			else
				i[1]++;
		}
		return (cmd->redir[i[0]] = '\0', (int)i[0] - 1);
	}
	return (len);
}

static void	fill_s_cmd(t_global *g, t_cmd *cmd, char *line, int ints[3])
{
	char	cmd_line[1024];
	char	*tmp;

	ints[0] = -1;
	while (line[++ints[0]])
		if (is_chr("><", line[ints[0]]) && !inq(line, ints[0], 0))
			break ;
	(init_cmd(cmd), ints[2] = fill_redir(g, cmd, line, ints[0]));
	ft_strncpy(cmd_line, line, ints[0]);
	ints[1] = ints[0];
	while (ints[0] < (int)ft_strlen(line) && line[ints[0]])
	{
		if (ints[0] < ints[2])
			ints[0] = ints[2];
		if (line[ints[0]] == 32 && !is_chr(">< \t", line[ints[0] - 1]))
			while (line[ints[0]] && !is_chr("><", line[ints[0]]))
				cmd_line[ints[1]++] = line[ints[0]++];
		ints[0]++;
	}
	cmd_line[ints[1]] = '\0';
	tmp = gest_expand(g, cmd_line);
	cmd->args = str2arr(tmp, " \t", true);
	free(tmp);
	if (!cmd->args)
		return (ft_perror(EALL, false), free_cmds(g), exit(1), (void)0);
}

void	init_s_cmd(t_global *g, char *line)
{
	char	**arr;
	int		rows;
	int		i;
	int		ints[3];

	rows = count_rows("|", line, true);
	g->cnt = rows;
	g->cmds = malloc(sizeof(t_cmd *) * (rows + 1));
	if (!g->cmds)
		return (ft_perror(EALL, false), exit(1), (void)0);
	arr = str2arr(line, "|", true);
	if (!arr)
		return (ft_perror(EALL, false), free_cmds(g), exit(1), (void)0);
	i = 0;
	while (i < rows)
	{
		g->cmds[i] = malloc(sizeof(t_cmd));
		if (!g->cmds[i])
			return (ft_perror(EALL, false), (void)0);
		fill_s_cmd(g, g->cmds[i], arr[i], ints);
		i++;
	}
	g->cmds[i] = NULL;
	free_arr(arr);
}
