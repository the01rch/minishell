/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:02:43 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/16 22:41:43 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str++);
}

bool	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (n <= 0)
		return (false);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		len;

	len = 0;
	while (src[len])
		len++;
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	len = 0;
	while (*src)
		dest[len++] = *src++;
	dest[len] = '\0';
	return (dest);
}
