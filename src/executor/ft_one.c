/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:20:05 by kpires            #+#    #+#             */
/*   Updated: 2024/12/23 23:04:35 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* is_error free needed and exit*/
int	close_fd(t_cmd *cmd, int *std_save, bool is_error)
{
	if (cmd->infile != -1)
	{
		if (dup2(std_save[0], 0) == -1 || is_error)
		{
			close(std_save[0]);
			if (cmd->outfile != -1)
				close(std_save[1]);
			if (is_error)
				exit(1);
		}
		close(std_save[0]);
	}
	if (cmd->outfile != -1)
	{
		if (dup2(std_save[1], 1) == -1 || is_error)
		{
			close(std_save[1]);
			if (is_error)
				exit(1);
		}
		close(std_save[1]);
	}
	return (1);
}

int	dup_inf_out(t_cmd *cmd, int *std_save)
{
	if (cmd->infile != -1)
	{
		std_save[0] = dup(0);
		if (std_save[0] == -1)
			return (1);
		if (dup2(cmd->infile, 0) == -1)
		{
			close(std_save[0]);
			return (1);
		}
	}
	if (cmd->outfile != -1)
	{
		std_save[1] = dup(1);
		if (std_save[1] == -1)
			return (close_fd(cmd, std_save, true));
		if (dup2(cmd->outfile, 1) == -1)
			return (close_fd(cmd, std_save, true));
	}
	return (0);
}
