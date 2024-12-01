/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:02:43 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/26 09:54:23 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

void free_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]); // Libère chaque chaîne
        i++;
    }
    free(arr); // Libère le tableau
}

bool	ft_strncmp2(char *s1, char *s2, int n)
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

char	*ft_strdup2(char *src)
{
	char	*dest;
	int		len;

	if (!src)
		return (NULL);
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
