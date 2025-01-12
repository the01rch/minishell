/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:10:04 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/12 21:37:01 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	bool	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}

t_state	is_format_export(char *str)
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

	tmp = lenv;
	while (tmp != NULL)
	{
		printf("export %s=\"%s\"\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	tmp = lenv;
}

static	bool	single_export(t_global *g, char *str, int i, t_env *tmp)
{
	char	*e_name;

	if (is_format_export(str) == NONE)
		return (true);
	if (is_format_export(str) == ERROR)
		return (g->exit_val = 1
			, ft_perror(EID, 0), false);
	while (str[i] && str[i] != '=')
		i++;
	e_name = ft_substr(str, 0, i);
	while (tmp)
	{
		if (ft_strcmp(e_name, tmp->name))
		{
			free(tmp->content);
			tmp->content = ft_substr(str, i + 1, ft_strlen(str));
			return (free(e_name), true);
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!ft_strcmp(e_name, tmp->name))
		tmp->next = create_node(str);
	return (free(e_name), true);
}

bool	ft_export(t_global *g, char **str, bool multiples)
{
	int		i;
	t_state	res;
	t_env	*tmp;
	bool	err;

	i = 0;
	tmp = g->lenv;
	if (!*str)
		return (print_export(g->lenv), true);
	if (!multiples)
		return (single_export(g, *str, 0, tmp), VALID);
	err = false;
	while (str[i] != NULL)
	{
		res = is_format_export(str[i]);
		if (res == ERROR || res == NONE)
		{
			if (res == ERROR)
				(ft_perror(EID, 0), err = true);
			i++;
			continue ;
		}
		single_export(g, str[i++], 0, tmp);
	}
	if (err)
		return (g->exit_val = 1, false);
	return (VALID);
}
