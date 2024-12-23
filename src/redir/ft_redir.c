/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:56:02 by kpires            #+#    #+#             */
/*   Updated: 2024/12/23 06:55:35 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_skipquotes(char *str, char quote)
{
	int	idx;

	idx = 0;
	if (str[idx] && str[idx] == quote)
	{
		idx++;
		while (str[idx] && str[idx] != quote)
			idx++;
		if (!str[idx])
			return (-1);
		if (str[idx])
			idx++;
	}
	return (idx);
}

static int	skip_nonredir(char *redir, int i)
{
	int	skipped;

	skipped = 0;
	while (redir[i + skipped] && !is_chr("><|", redir[i + skipped]))
	{
		if (!is_chr("'\"", redir[i + skipped]))
			skipped++;
		skipped += ft_skipquotes(redir + i + skipped, '"');
		skipped += ft_skipquotes(redir + i + skipped, '\'');
	}
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
