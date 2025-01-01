/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:14:52 by kpires            #+#    #+#             */
/*   Updated: 2025/01/01 18:39:21 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_all_fd_child(t_global *g)
{
	int	i;

	i = 0;
	while (i < g->cnt)
	{
		if (g->cmds[i].infile > 2)
			close(g->cmds[i].infile);
		if (g->cmds[i].outfile > 2)
			close(g->cmds[i].outfile);
		i++;
	}
}
