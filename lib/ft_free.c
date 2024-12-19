/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:11 by kpires            #+#    #+#             */
/*   Updated: 2024/12/19 12:55:34 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

void	free_arr(char **arr)
{
	if (!arr)
		return ;
	while (*arr != NULL)
	{
		free(*arr);
		arr++;
	}
}

/*
void	free_cmds(t_command **cmds)
{
	int		i;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->exec)
			free(cmds[i]->exec);
		if (cmds[i]->args)
			free(cmds[i]->args);
		if (cmds[i]->full)
			free(cmds[i]->full);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
*/

void	free_node(t_env *node)
{
	if (node)
	{
		free(node->name);
		free(node->content);
		free(node);
	}
}
