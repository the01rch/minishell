/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:48:41 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/04 20:49:49 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_putchar(char c)
{
	write(2, &c, 1);
}

void	ft_perror(const char *str)
{
	while (*str)
		ft_putchar(*str++);
}
