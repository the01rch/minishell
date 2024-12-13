/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:22:03 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/11 18:01:08 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

char	*ft_concat(char *str, char *str2)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(str2) + 1));
	if (!tmp)
		return (NULL);
	while (*str)
		tmp[i++] = *str++;
	while (str2[j])
		tmp[i++] = str2[j++];
	tmp[i] = 0;
	return (tmp);
}
