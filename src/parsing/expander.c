/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:27:02 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/04 22:04:08 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	inq(char *str, int index, char quote)
{
	int		i;
	char	current;

	i = 0;
	current = '\0';
	if (!str || index < 0 || index >= ft_strlen(str))
		return (false);
	while (i <= index)
	{
		if (current == '\0')
		{
			if ((quote == '\0' && (str[i] == 34 || str[i] == 39))
				|| str[i] == quote)
				current = str[i];
		}
		else if (str[i] == current)
			current = '\0';
		i++;
	}
	return (current != '\0');
}

char	*remq(char *str)
{
    char	*res;
    int		len;
    int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
    res = malloc(sizeof(char) * (len + 1));
    if (!res)
        return (NULL);
    while (str[i]) {
        if (str[i] != '"' && str[i] != '\'')
            res[j++] = str[i];
        i++;
    }
    res[j] = '\0';
    return (res);
}

char	*ret_venv(t_env *lenv, char *src, int *i)
{
	char	*str;
	char	*res;
	int		len;

	len = 0;
	while (src[len] && (ft_isalnum(src[len]) || src[len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	*i += len;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (printf(EALL), NULL);
	ft_strncpy(str, src, len);
	res = plist(lenv, str);
	free(str);
	if (!res)
		return (NULL);
	return (res);
}

#ifndef BUF_SIZ
# define BUF_SIZ

# define BUFF_SIZ 256

char	*gest_expand(t_global *g, char *str)
{
	char	*buf;
	char	*res;
	int		i;
	int		y;

	buf = ft_calloc(sizeof(char), BUFF_SIZ);
	if (!buf)
		return (printf(EALL), NULL);
	i = 0;
	y = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && !inq(str, i, '\''))
		{
			i++;
			if (str[i] == '?')
			{
				res = ft_itoa(g->exit_val);
				for (int b = 0; res[b]; b++)
					buf[y++] = res[b];
				free(res);
				i++;
				continue ;
			}
			res = ret_venv(g->lenv, &str[i], &i);
			if (!res)
				continue ;
			for (int b = 0; res[b]; b++)
				buf[y++] = res[b];
			free(res);
		}
		else
			buf[y++] = str[i++];
	}
	buf[y] = '\0';
	return (remq(buf));
}
#endif
