/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:48:41 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/11 12:52:47 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_putchar(char c)
{
	write(2, &c, 1);
}

void	ft_perror(const char *str, bool new_line)
{
	while (*str)
		ft_putchar(*str++);
	if (new_line)
		ft_putchar('\n');
}
