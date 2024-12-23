/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 06:04:27 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/23 06:21:02 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*pwrapper(char *name, char *content, char sep)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen(name) + ft_strlen(content) + 1;
	i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (*name)
		dest[i++] = *name++;
	dest[i++] = sep;
	while (*content)
		dest[i++] = *content++;
	dest[i] = '\0';
	return (dest);
}

int	skip_spaces(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && (is_chr("\t ", str[i])))
		i++;
	return (i);
}
