/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whitespaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:53:56 by kpires            #+#    #+#             */
/*   Updated: 2024/12/18 08:57:32 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

int ft_skip_whitespaces(char *str)
{
    int i;

    if (!str)
        return (0);
    i = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    return (i);
}
