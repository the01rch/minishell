/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:01:39 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/20 19:55:07 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

static int	check_pipes(char *str)
{
	int	idx;

	idx = 1;
	if (*str != '|')
		return (0);
	while (is_chr("\t ", idx))
		idx++;
	if (!str[idx] || str[idx] == '|')
		return (printf("%s", FPIPE), -1);
	idx++;
	return (1);
}

static int	check_redir(char *str)
{
	int	idx;

	if (!*str || !is_chr("><", *str))
		return (0);
	idx = 0;
	if (ft_strncmp(&str[idx], ">>", 2) == 0)
		idx += 2;
	else if (str[idx] == '>')
		idx++;
	else if (ft_strncmp(&str[idx], "<<", 2) == 0)
		idx += 2;
	else if (str[idx] == '<')
		idx++;
	while (str[idx] && is_chr("\t ", str[idx]))
		idx++;
	if (!str[idx])
		return (printf("Error: Token\n"), -1);
	if (is_chr("><|", str[idx]))
		return (printf("Error: Token\n"), -1);
	return (idx);
}

static int	check_quotes(char *str, int i)
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
		return (-1);
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
	tmp = check_pipes(&str[i]);
	if (tmp < 0)
		return (-1);
	i += tmp;
	tmp = check_redir(&str[i]);
	if (tmp < 0)
		return (-1);
	i += tmp;
	return (i);
}

bool	is_syntax_valid(char *str)
{
	int	i;
	int	tmp;

	if (!str)
		return (false);
	add_history(str);
	i = 0;
	while (str[i] && is_chr("\t ", str[i]))
		i++;
	if (str[i] == '|')
		return (printf("%s", FPIPE), false);
	while (str[i])
	{
		tmp = token_indices(str, i);
		if (tmp < 0)
			return (false);
		i += tmp;
	}
	return (true);
}
