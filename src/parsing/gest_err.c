/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:01:39 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/01 18:00:12 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_pipes(char *str)
{
	int		idx;
	int		len;

	if (*str != '|')
		return (0);
	len = ft_strlen(str);
	idx = 1;
	idx += skip_spaces(str);
	if (idx >= len || str[idx] == '|')
		return (printf("%s", FPIPE), -1);
	return (1);
}

static int	check_redir(char *str)
{
	int		idx;
	int		len;

	if (!*str || !is_chr("><", *str))
		return (0);
	len = ft_strlen(str);
	idx = 0;
	if (idx + 1 < len && ft_strncmp(&str[idx], ">>", 2) == 0)
		idx += 2;
	else if (*str == '>')
		idx++;
	else if (idx + 1 < len && ft_strncmp(&str[idx], "<<", 2) == 0)
		idx += 2;
	else if (*str == '<')
		idx++;
	while (idx < len && is_chr("\t ", str[idx]))
		idx++;
	if (idx >= len)
		return (printf("Error: Token\n"), -1);
	if (is_chr("><|", str[idx]))
		return (printf("Error: Token\n"), -1);
	return (idx);
}

int	check_quotes(char *str, int i)
{
	char	openq;
	int		idx;

	openq = 0;
	idx = 0;
	if (str[i] == 34 || str[i] == 39)
	{
		idx = i;
		while (str[idx])
		{
			if (openq == 0 && (str[idx] == 34 || str[idx] == 39))
				openq = str[idx];
			else if (str[idx] == openq)
				openq = 0;
			idx++;
		}
	}
	if (openq != 0)
	{
		printf("Error: Quote\n");
		return (-1);
	}
	return (idx);
}

static int	token_indices(char *str, int i)
{
	int	tmp;

	tmp = 0;
	while (str[i] && !is_chr("><|\"'", str[i]))
		i++;
	tmp = check_quotes(str, i);
	if (tmp < 0)
		return (-1);
	i += tmp;
	if (i <= ft_strlen(str))
		tmp = check_pipes(str + i);
	if (tmp < 0)
		return (-1);
	i += tmp;
	if (i <= ft_strlen(str))
		tmp = check_redir(str + i);
	if (tmp < 0)
		return (-1);
	i += tmp;
	return (i);
}

bool	is_syntax_valid(t_global *g, char *str, t_env *lenv)
{
	int	i;
	int	tmp;

	if (g_signal == SIGINT)
		g->exit_val = 130;
	if (str == NULL)
		(free_list(lenv), signal_ctrd(g));
	add_history(str);
	i = skip_spaces(str);
	if (!str[i])
		return (false);
	if (str[i] == '|')
		return (printf("%s", FPIPE), false);
	while (str[i])
	{
		tmp = token_indices(str, i);
		if (tmp < 0)
			return (false);
		i += tmp;
		if (i > ft_strlen(str))
			break ;
	}
	return (true);
}
