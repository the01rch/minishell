/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:56:02 by kpires            #+#    #+#             */
/*   Updated: 2024/12/19 10:15:37 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../icl/minishell.h"

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

static int	skip_nonredir(char *line, int i)
{
	int	skipped;

	skipped = 0;
	while (line[i + skipped] && !is_in_set(line[i + skipped], "><|"))
	{
		if (!is_in_set(line[i + skipped], "'\""))
			skipped++;
		skipped += ft_skipquotes(line + i + skipped, '"');
		skipped += ft_skipquotes(line + i + skipped, '\'');
	}
	return (skipped);
}

static int	skip_cmd(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '|')
		i++;
	return (i);
}

int	ft_redir(t_command *cmd, char *line)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	printf("ft_redir\n");
	while (line[i])
	{
		if (ft_str_inc(line + i, ">>", 2))
			tmp = ft_append(cmd, line + i + 2);
		else if (line[i] == '>')
			tmp = ft_overwrite(cmd, line + i + 1);
		if (ft_str_inc(line + i, "<<", 2))
			tmp = ft_append(cmd, line + i + 2);
		else if (line[i] == '<')
			tmp = ft_redirect_input(cmd, line + i + 1);
		if (tmp < 0)
			i += skip_cmd(line + i);
		if (!line[i])
			return (1);
		i += tmp;
		i += skip_nonredir(line, i);
	}
	return (1);
}
