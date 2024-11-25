/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:49:07 by kpires            #+#    #+#             */
/*   Updated: 2024/11/25 14:49:07 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

char    *shell_getenv(char *var, char **env, int n)
{
    int i;
    int n2;

    i = 0;
    if (n < 0)
        n = ft_strlen(var);
    while (!ft_strchr(var, '=') && env && env[i])
    {
        n2 = n;
        if (n2 < ft_strchr_i(env[i], '='))
            n2 = ft_strchr_i(env[i], '=');
        if (!ft_strncmp(env[i], var, n2))
            return (ft_substr(env[i], n2 + 1, ft_strlen(env[i])));
        i++;
    }
    return (NULL);
}

char    **shell_setenv(char *var, char *value, char **env, int n)
{
    int     i[2];
    char    *aux[2];

    if (n < 0)
        n = ft_strlen(var);
    i[0] = -1;
    aux[0] = ft_strjoin(var, "=");
    aux[1] = ft_strjoin(aux[0], value);
    free(aux[0]);
    while (!ft_strchr(var, '=') && env && env[++i[0]])
    {
        i[1] = n;
        if (i[1] < ft_strchr_i(env[i[0]], '='))
            i[1] = ft_strchr_i(env[i[0]], '=');
        if (!ft_strncmp(env[i[0]], var, i[1]))
        {
            aux[0] = env[i[0]];
            env[i[0]] = aux[1];
            free(aux[0]);
            return (env);
        }
    }
    env = ft_extend_matrix(env, aux[1]);
    free(aux[1]);
    return (env);
}