/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 22:55:23 by kpires            #+#    #+#             */
/*   Updated: 2025/01/04 06:59:27 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	fsize;

	if (!nmemb || !size)
		return (malloc(1));
	fsize = nmemb * size;
	if ((fsize < size) || (fsize < nmemb))
		return (NULL);
	ptr = malloc(fsize);
	if (!ptr)
		return (NULL);
	return (ft_memset(ptr, 0, fsize));
}
