/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:11 by kpires            #+#    #+#             */
/*   Updated: 2024/12/13 17:53:09 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_cmds(t_command **cmds)
{
	int		i;

	i = 0;
	while (cmds[i])
	{
		free(cmds[i]->exec);
		if (cmds[i]->args)
			free(cmds[i]->args);
		free(cmds[i]->full);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	free_global(t_global *global)
{
	free_list(global->env_list);
	free_cmds(global->cmds);
	free_arr(global->env);
	free_arr(global->argv);
	free_arr(global->full);
	free(global->cmds);
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
