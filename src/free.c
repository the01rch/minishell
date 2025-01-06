/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:11 by kpires            #+#    #+#             */
/*   Updated: 2025/01/06 17:30:58 by kpires           ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)
{
	if (cmd->args)
	{
		free_arr(cmd->args);
	}
	if (cmd->redir)
		free(cmd->redir);
	free(cmd);
}

void	free_cmds(t_global *g)
{
	int	i;

	if (!g || !g->cmds)
		return ;
	close_all_fd_child(g);
	i = 0;
	while (g->cmds[i])
	{
		free_cmd(g->cmds[i]);
		g->cmds[i] = NULL;
		i++;
	}
	free(g->cmds);
	g->cmds = NULL;
}
