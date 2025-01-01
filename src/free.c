/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:11 by kpires            #+#    #+#             */
/*   Updated: 2025/01/01 18:07:30 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_node(t_env *node)
{
	if (node)
	{
		free(node->name);
		free(node->content);
		free(node);
	}
}

void	free_list(t_env *list)
{
	t_env	*tmp;

	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		free_node(tmp);
	}
}

void	free_cmds(t_global *g)
{
	int	i;

	i = 0;
	if (!g->cmds)
		return ;
	while (i < g->cnt)
	{
		if (g->cmds[i].redir)
		{
			free(g->cmds[i].redir);
			g->cmds[i].redir = NULL;
		}
		if (g->cmds[i].args)
		{
			free_arr(g->cmds[i].args);
			g->cmds[i].args = NULL;
		}
		i++;
	}
	free(g->cmds);
	g->cmds = NULL;
}
