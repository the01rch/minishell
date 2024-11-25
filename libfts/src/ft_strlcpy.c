/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires   <kpires@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:08:56 by kpires            #+#    #+#             */
/*   Updated: 2024/09/27 16:28:04 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			size_src;

	i = 0;
	if (src == NULL)
		return (0);
	size_src = ft_strlen(src);
	if ((int)size < 0)
		size = size_src + 1;
	if (size >= 2 && size_src != 0)
	{
		while (i < size - 1)
		{
			if (i < size_src)
				dst[i] = src[i];
			else if (i == size_src)
				dst[i] = '\0';
			i++;
		}
	}
	if (size != 0)
		dst[i] = '\0';
	return (size_src);
}
