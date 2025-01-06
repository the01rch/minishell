/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:01:39 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/06 11:08:08 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_pipes(char *str)
{
	int		idx;

	if (*str != '|')
		return (0);
	idx = 1;
	idx += skip_spaces(str);
	if (!str[idx] || str[idx] == '|')
		return (ft_perror(FPIPE), -1);
	return (1);
}

static int	check_redir(char *str)
{
	int		idx;

	if (!*str || !is_chr("><", *str))
		return (0);
	idx = 0;
	if (ft_strncmp(str + idx, ">>", 2) == 0)
		idx += 2;
	else if (str[idx] == '>')
		idx++;
	else if (ft_strncmp(str + idx, "<<", 2) == 0)
		idx += 2;
	else if (str[idx] == '<')
		idx++;
	while (str[idx] && is_chr("\t ", str[idx]))
		idx++;
	if (!str[idx])
	{
		return (ft_perror(FPIPE), -1);
	}
	if (is_chr("><|", str[idx]))
	{
		return (ft_perror(FPIPE), -1);
	}
	return (idx);
}

int check_quotes(char *str, int i)
{
    char	openq;
    int		idx;

	openq = 0;
	idx = i;
    while (str[idx])
    {
        if (openq == 0 && (str[idx] == 34 || str[idx] == 39)) 
            openq = str[idx];
        else if (openq != 0 && str[idx] == openq) 
            openq = 0; 
        idx++;
    }
    if (openq != 0)
        return (printf("Error: Unmatched quote\n"), -1);
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
		return (ft_perror(" syntax error"), -1);
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
	i = skip_spaces(str);
	if (!str[i])
	{
		g->exit_val = 2;
		return (false);
	}
	if (str[i] == '|')
	{
		g->exit_val = 2;
		return (ft_perror(FPIPE), false);
	}
	while (str[i])
	{
		tmp = token_indices(str, i);
		if (tmp < 0)
		{
			g->exit_val = 2;
			return (false);
		}
		i += tmp;
		if (i > ft_strlen(str))
			break ;
	}
	add_history(str);
	return (true);
}
