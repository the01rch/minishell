/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_nb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 22:18:11 by kpires            #+#    #+#             */
/*   Updated: 2025/01/02 22:19:31 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_nb(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == 32 || cmd[i] == '\0')
	{
		if (cmd[i] == '\0')
			return (1);
		i++;
	}
	if (cmd[i] == '+' || cmd[i] == '-')
		i++;
	while (ft_isdigit(cmd[i]))
		i++;
	while (cmd[i] == 32)
		i++;
	if (cmd[i] != '\0')
		return (1);
	return (0);
}