/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:10:04 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/09 23:22:58 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_state is_format_export(char *str)
{
	bool	equal;

	equal = false;
//	printf("str : %s\n", str);
	while (*str)
	{
		if (*str == '=')
			equal = true;
		if (!equal)
		{
			if (!ft_isalnum(*str) || *str != '_')
				return (ERROR);
		}
		str++;
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
		printf("export %s\n", test);
		free(test);
		tmp = tmp->next;
	}
	tmp = lenv;
}

static	bool single_export(t_global *g, char *str)
{
	t_env	*tmp;
	char	*test;
	int		i;

	tmp = g->lenv;
	i = 0;
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
	tmp->next = create_node(str);
	return (free(test), true);
}

t_state	ft_export(t_global *g, char **str)
{
	int		i;

	i = 0;
	if (!*str)
		return (print_export(g->lenv), true);
	while (str[i] != NULL)
		i++;
	if (i > 1)	
	{
		i = 0;
		while (str[i] != NULL)
		{
			if (is_format_export(str[i]) == ERROR)
				return (g->exit_val = 1, ft_perror("not a valid identifier\n"), ERROR);
			else if (is_format_export(str[i]) == NONE)
			{
				i++;
				continue ;
			}
			single_export(g, str[i++]);
		}
	}	
	else
		single_export(g, *str);
	return (VALID);
}
