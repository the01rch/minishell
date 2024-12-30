/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:11 by kpires            #+#    #+#             */
/*   Updated: 2024/12/28 18:58:21 by redrouic         ###   ########.fr       */
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
/*
void	free_all(t_cmd **cmd)
{
	int	i;
	
	i = 0;
	if (!cmd)
		return ;
	while ()
	{
		if (cmd[i]->redir)
			free(cmd[i]->redir);
		if (cmd[i]->args)
			free_arr(cmd[i]->args);
		i++;
	}
	free_list(list);
	free(line);
}
*/
