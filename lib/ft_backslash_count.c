/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backslash_count.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:57:10 by kpires            #+#    #+#             */
/*   Updated: 2024/12/18 09:05:01 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

int ft_backslash_count(char *str)
{
    int i;
    int back;

    if (!str)
        return (0);
    i = 0;
    back = 0;
    while(str[i])
    {
        if (str[i] == '\\')
            back++;
        i++;
    }
    return (back);
}
