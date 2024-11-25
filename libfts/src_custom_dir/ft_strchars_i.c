/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchars_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires   <kpires  @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:42:42 by kpires            #+#    #+#             */
/*   Updated: 2024/11/04 12:35:43 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strchars_i(const char *s, char *set)
{
	int				i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (-1);
}
