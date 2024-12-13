/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:23:41 by kpires            #+#    #+#             */
/*   Updated: 2024/12/13 16:46:27 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

t_state	ft_redir(t_global *global)
{
	int			i;
	t_command	**cmd;

	i = 0;
	cmd = global->cmds;
	while (cmd[i] && cmd[i]->full)
	{
		if (ft_strcmp(cmd[i]->full, ">>"))
			printf("ft_redir >>\n");
		else if (ft_strcmp(cmd[i]->full, ">"))
			printf("ft_redir >\n");
		else if (ft_strcmp(cmd[i]->full, "<"))
			printf("ft_redir <\n");
		else if (ft_strcmp(cmd[i]->full, "<<"))
			printf("ft_redir <<\n");
		i++;
	}
	return (NONE);
}
