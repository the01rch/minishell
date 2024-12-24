/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:56:02 by kpires            #+#    #+#             */
/*   Updated: 2024/12/24 01:30:33 by kpires           ###   ########.fr       */
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

static int	skip_nonredir(char *redir, int i)
{
	int	skipped;

	skipped = -1;
	while (redir[i + skipped] && !is_chr("><|", redir[i + skipped]))
	{
		if (!is_chr("'\"", redir[i + skipped]))
			skipped++;
		if (check_quotes(redir + i + skipped, 0) > 0)
			skipped += check_quotes(redir + i + skipped, 0);
	}
	if (skipped == -1)
		return (0);
	return (skipped);
}

static int	skip_cmd(char *redir)
{
	int	i;

	i = 0;
	while (redir[i] && redir[i] != '|')
		i++;
	return (i);
}

int	ft_redir(t_cmd *cmd, t_env *lenv)
{
	int	i;
	int	tmp;

	if (!cmd || !cmd->redir)
		return (1);
	i = 0;
	tmp = 0;
	while (cmd->redir[i])
	{
		if (ft_strncmp(cmd->redir + i, ">>", 2) == 0)
			tmp = ft_append(cmd, cmd->redir + i + 2);
		else if (cmd->redir[i] == '>')
			tmp = ft_overwrite(cmd, cmd->redir + i + 1);
		if (ft_strncmp(cmd->redir + i, "<<", 2) == 0)
			tmp = ft_heredoc(cmd, cmd->redir + i + 2, lenv);
		else if (cmd->redir[i] == '<')
			tmp = ft_redirect_input(cmd, cmd->redir + i + 1);
		if (tmp < 0)
			i += skip_cmd(cmd->redir + i);
		if (!cmd->redir[i])
			return (1);
		i += tmp;
		i += skip_nonredir(cmd->redir, i);
	}
	return (1);
}
