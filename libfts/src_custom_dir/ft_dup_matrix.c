/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires   <kpires  @student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:54:58 by kpires            #+#    #+#             */
/*   Updated: 2024/10/22 16:05:04 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	**ft_dup_matrix(char **m)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = ft_matrixlen(m);
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (m[i])
	{
		out[i] = ft_strdup(m[i]);
		if (!out[i])
		{
			ft_free_matrix(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}
