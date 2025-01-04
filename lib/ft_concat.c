/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:22:03 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/04 07:30:55 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (s[i] && i != n)
		i++;
	return (i);
}

void	ft_strncat(char *dest, char *src, size_t n)
{
	int		i;
	int		j;

	i = n;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j++];
		i++;
	}
	dest[ft_strnlen(dest, n)] = '\0';
}
