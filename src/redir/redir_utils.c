/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:02:53 by kpires            #+#    #+#             */
/*   Updated: 2025/01/10 20:37:23 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_fname_len(char *redir, char *dels)
{
	int		i;
	char	q;
	int		real_len;

	i = skip_spaces(redir);
	q = '\0';
	real_len = 0;
	while (redir[i] && (!is_chr(dels, redir[i])
			|| (is_chr("'\"", q) && redir[i] != q)))
	{
		if (is_chr("'\"", redir[i]) && !q)
			q = redir[i];
		else if (redir[i] == q)
			q = '\0';
		else
			real_len++;
		i++;
	}
	return (real_len);
}

char	*ft_fname(char *redir, int i, int len, char *dels)
{
	char	*file;
	char	q;

	file = malloc(sizeof(char) * (count_fname_len(redir, dels) + 1));
	if (!file)
		return (NULL);
	i = skip_spaces(redir) - 1;
	q = '\0';
	while (redir[++i] && (!is_chr(dels, redir[i])
			|| (is_chr("'\"", q) && redir[i] != q)))
	{
		if ((is_chr("'\"", redir[i]) && !q) || redir[i] == q)
		{
			if (redir[i] == q)
				q = '\0';
			else
				q = redir[i];
			continue ;
		}
		file[len++] = redir[i];
	}
	if (!q)
		if (len > 0 && file[len - 1] == ' ')
			len--;
	return (file[len] = '\0', file);
}

int	ft_skipquotes(char *str, char quote)
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

void	handl_heredoc(int sig)
{
	g_signal = sig;
	close(STDIN_FILENO);
}
