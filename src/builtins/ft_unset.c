/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:58:06 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/11 17:03:47 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	unset_var(t_env **lenv, char *var)
{
	t_env	*tmp;
	t_env	*to_delete;

	tmp = *lenv;
	if (ft_strcmp(var, (*lenv)->name))
	{
		to_delete = *lenv;
		*lenv = (*lenv)->next;
		free_node(to_delete);
		return ;
	}
	while (tmp && tmp->next)
	{
		if (ft_strcmp(var, tmp->next->name))
		{
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			free_node(to_delete);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(t_global *g, char **str)
{
	int	i;

	i = 0;
	if (!g->lenv || !str)
		return ;
	g->exit_val = 0;
	while (str[i] != NULL)
	{
		if (is_format_export(str[i]) == ERROR)
		{
			g->exit_val = 1;
			ft_perror(" not a valid identifier\n");
			return ;
		}
		unset_var(&g->lenv, str[i]);
		i++;
	}
}
/*
void	ft_unset(t_global *g, char **str)
{
	t_env	*tmp;
	t_env	*to_delete;
	int		i;

	i = 0;
	if (!g->lenv || !str)
		return ;
	g->exit_val = 0;
	while (str[i] != NULL)
	{
		if (is_format_export(str[i]) == ERROR)
			return (g->exit_val = 1,
					ft_perror(" not a valid identifier\n"), (void)0);
		tmp = g->lenv;
		if (ft_strcmp(str[i], g->lenv->name))
		{
			to_delete = g->lenv;
			g->lenv = g->lenv->next;
			free_node(to_delete);
			break ;
		}
		while (tmp && tmp->next)
		{
			if (ft_strcmp(str[i], tmp->next->name))
			{
				to_delete = tmp->next;
				tmp->next = tmp->next->next;
				free_node(to_delete);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}
*/
