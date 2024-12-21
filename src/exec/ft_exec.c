/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:30:38 by kpires            #+#    #+#             */
/*   Updated: 2024/12/20 23:48:24 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../icl/minishell.h"

void	ft_exec(t_cmd cmd, t_env *list)
{
	if (gest_builtins(list, &cmd) == NONE)
		gest_shell(list, &cmd);
}
