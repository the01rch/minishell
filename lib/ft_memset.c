/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 22:56:21 by kpires            #+#    #+#             */
/*   Updated: 2024/12/23 22:46:29 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_memset(void *p, int i, size_t len)
{
	char	*c;

	c = p;
	while (len)
	{
		*c = (unsigned char) i;
		c++;
		len--;
	}
	return (p);
}
