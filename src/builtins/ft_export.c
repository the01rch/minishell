/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:10:04 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/11 12:57:10 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	bool	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}

static t_state	is_format_export(char *str)
{
	bool	equal;
	int		i;

	equal = false;
	if (!is_alpha(str[0]) && str[0] != '_')
		return (ERROR);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			equal = true;
			break ;
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (ERROR);
		i++;
	}
	if (!equal)
		return (NONE);
	return (VALID);
}

static void	print_export(t_env *lenv)
{
	t_env	*tmp;
	char	*test;

	tmp = lenv;
	while (tmp->next != NULL)
	{
		test = pwrapper(tmp->name, tmp->content, '=');
		free(test);
		tmp = tmp->next;
	}
	tmp = lenv;
}

static	bool	single_export(t_global *g, char *str)
{
	t_env	*tmp;
	char	*test;
	int		i;

	tmp = g->lenv;
	i = 0;
	if (is_format_export(str) == NONE)
		return (true);
	if (is_format_export(str) == ERROR)
		return (g->exit_val = 1
			, ft_perror(" not a valid identifier\n", false), false);
	while (str[i] && str[i] != '=')
		i++;
	test = ft_substr(str, 0, i);
	while (tmp->next != NULL)
	{
		if (ft_strcmp(test, tmp->name))
		{
			(free(tmp->content));
			tmp->content = ft_substr(str, i + 1, ft_strlen(str));
			return (free(test), true);
		}
		tmp = tmp->next;
	}
	return (tmp->next = create_node(str), free(test), true);
}

bool	ft_export(t_global *g, char **str, bool multiples)
{
	int		i;
	t_state	res;

	i = 0;
	if (!*str)
		return (print_export(g->lenv), true);
	if (!multiples)
		return (single_export(g, *str), VALID);
	while (str[i] != NULL)
	{
		res = is_format_export(str[i]);
		if (res == ERROR)
			return (g->exit_val = 1,
				ft_perror(" not a valid identifier\n", false), false);
		if (res == NONE)
		{
			i++;
			continue ;
		}
		single_export(g, str[i++]);
	}
	return (VALID);
}
