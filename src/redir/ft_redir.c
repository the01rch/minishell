/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:56:02 by kpires            #+#    #+#             */
/*   Updated: 2025/01/10 10:55:46 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

ssize_t	write_here(const void *buffer, int fd, size_t count)
{
	const char	*buf;
	size_t		total;
	ssize_t		bytes;

	buf = buffer;
	total = 0;
	while (total < count)
	{
		bytes = write(fd, buf + total, count - total);
		if (bytes > 0)
			total += bytes;
		else if (bytes == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				continue ;
			else
				return (-1);
		}
	}
	write(fd, "\n", 1);
	return (total);
}

int	extract_varlen(char *line, int len, char **v_name, bool del_sign)
{
	int	start;
	int	var_len;

	start = len;
	while (line[len] && (ft_isalnum(line[len]) || line[len] == '_'))
		len++;
	var_len = len - start;
	if (line[len] && del_sign)
		len--;
	*v_name = malloc(sizeof(char) * (var_len + 1));
	if (!*v_name)
		return (-1);
	ft_strncpy(*v_name, line + start, var_len);
	(*v_name)[var_len] = '\0';
	return (len);
}

int	ft_redir(t_global *g, int i)
{
	int		j;
	char	**redir;

	redir = malloc(sizeof(char *) * 1 + 1);
	if (!redir)
		return (-1);
	redir[0] = "   			<< \"ONE \"";
	redir[1] = NULL;
	while (++i < g->cnt && g->cmds[i])
	{
		if (!g->cmds[i]->redir)
			continue ;
		j = 0;
		while (redir[j])
		{
			if (!g->cmds[i]->redir)
				break ;
			redir[j] += skip_spaces(redir[j]);
			if (ft_strncmp(redir[j], ">>", 2) == 0)
				ft_append(g, g->cmds[i], redir[j] + 2);
			else if (redir[j][0] == '>')
				ft_overwrite(g, g->cmds[i], redir[j] + 1);
			if (ft_strncmp(redir[j], "<<", 2) == 0)
				ft_heredoc(g, i, redir[j] + 2);
			else if (redir[j][0] == '<')
				ft_redir_input(g, g->cmds[i], redir[j] + 1);
			j++;
		}
	}
	return (1);
}
