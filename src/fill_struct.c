/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:02:03 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/10 15:08:54 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	debug = false;

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

static void concat_quoted_string(char *dest, char *line, int *i, int *j, int len)
{
	char quote_char;

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
			break;
	}
}

static int fill_redir(t_global *g, t_cmd *cmd, char *line, int len)
{
	int		i;
	int		j;
	bool	q;

	q = false;
	if (len < (int)ft_strlen(line))
	{
		cmd->redir = malloc(sizeof(char) * (ft_strlen(line) - len + 1));
		if (!cmd->redir)
			return (printf("%s", EALL), free_cmds(g), exit(1), (int)len);
		i = 0;
		j = len;
		while (j < (int)ft_strlen(line))
		{
			if (!q && is_chr("><", line[j]))
			{
				while (j < (int)ft_strlen(line) && (is_chr("><", line[j]) || is_chr(" \t", line[j])))
					cmd->redir[i++] = line[j++];
				concat_quoted_string(cmd->redir, line, &i, &j, ft_strlen(line));
				cmd->redir[i++] = ' ';
			}
			else
				j++;
		}
		cmd->redir[i] = '\0';
		if (debug)
			printf("redir: [%s]\n", cmd->redir);
		return (i - 1);
	}
	return (len);
}

static void	fill_s_cmd(t_global *g, t_cmd *cmd, char *line)
{
    char	cmd_line[1024];
    char	*tmp;
    int		i;
    int		w;
	int		test;

    i = 0;
    while (line[i])
    {
        if (is_chr("><", line[i]) && !inq(line, i, 0))
            break ;
        i++;
    }
    init_cmd(cmd);
    test = fill_redir(g, cmd, line, i);
	if (debug)
		printf("redir + test + i: [%s]\n", line + test + i);
    ft_strncpy(cmd_line, line, i);
    w = i;
    while (i < (int)ft_strlen(line) && line[i])
    {
		if (i < test)
			i = test;
        if (line[i] == 32 && !is_chr(">< \t", line[i - 1]))
        {
            while (line[i] && !is_chr("><", line[i]))
                cmd_line[w++] = line[i++];
        }
        i++;
    }
    cmd_line[w] = '\0';
	if (debug)
    	printf("cmd_line: [%s]\n", cmd_line);
    tmp = gest_expand(g, cmd_line);
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
