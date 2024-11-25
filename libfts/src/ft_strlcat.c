/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires   <kpires@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:09:17 by kpires            #+#    #+#             */
/*   Updated: 2024/09/27 16:19:50 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char			*ptr;
	unsigned int	i;

	if (size < ft_strlen(dst))
		return (ft_strlen(src) + size);
	ptr = dst + ft_strlen(dst);
	i = ft_strlen(dst);
	while (i < size - 1 && *src != '\0' && size >= 2)
	{
		*ptr = *src;
		ptr++;
		src++;
		i++;
	}
	if (size != 0)
		*ptr = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}
