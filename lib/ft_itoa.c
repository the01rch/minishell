/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:42:32 by kpires            #+#    #+#             */
/*   Updated: 2024/12/23 22:46:07 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	ft_nbrlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*res;
	size_t			len;
	unsigned int	nb;

	len = ft_nbrlen(n);
	res = ft_calloc(len + 1, 1);
	if (!res)
		return (NULL);
	nb = n;
	if (n < 0)
		nb = -n;
	while (len--)
	{
		res[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
