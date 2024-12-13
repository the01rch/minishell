/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:27:02 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/13 17:44:15 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

bool	is_unclosed(char *str)
{
	char	openq;
	int		i;

	openq = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (openq == 0)
				openq = str[i];
			else if (str[i] == openq)
				openq = 0;
		}
		i++;
	}
	return (openq == 0);
}

bool	inq(char *str, int index, char quote)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (quote != 0 && str[i] == quote)
			return (true);
		else if (quote == 0 && (str[i] == 34 || str[i] == 39))
			return (true);
		i++;
	}
	return (false);
}

char	*remq(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str)));
	while (str[i])
	{
		if ((str[i] != 34 && !inq(str, i, 0))
			&& (str[i] != 39 && !inq(str, i, 0)))
			res[j++] = str[i];
		i++;
	}
	res[j] = 0;
	return (res);
}

bool	is_quoted(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (true);
		i++;
	}
	return (false);
}

char	*gest_sign(t_env *lenv, char *str, int i)
{
	char	*copy;
	char	*res;

	copy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!copy)
		return (NULL);
	ft_strncpy(copy, str, ft_strlen(str));
	if (is_quoted(copy) && !is_unclosed(copy))
		return (free(copy), "");
	while (copy[i])
	{
		if (copy[0] == 36)
		{
			res = plist(lenv, &copy[1]);
			if (!res)
				return (free(copy), "");
			return (free(copy), ft_strdup(res));
		}
		if (copy[i] == 36 && inq(copy, i, 34))
			return (free(copy), ft_strdup(update_venv(lenv, copy)));
		i++;
	}
	if (is_quoted(copy))
		return (free(copy), ft_strdup(remq(copy)));
	return (free(copy), str);
}
