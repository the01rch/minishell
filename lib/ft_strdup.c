/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:23:16 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/11 18:26:20 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	int		len;

	len = 0;
	if (!src)
		return (NULL);
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
