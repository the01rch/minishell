/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:27:02 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/23 09:31:12 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*update_venv(t_env *lenv, char *str)
{
	char	*check;
	char	*res;
	int		len;

	len = 0;
	while (str[len] && str[len] != 32)
		len++;
	check = malloc(sizeof(char) * len + 1);
	ft_strncpy(check, str, len);
	if (inq(check, 1, 0))
		check = ft_strdup(remq(check));
	res = plist(lenv, &check[1]);
	if (res && len == ft_strlen(str))
		return (free(check), res);
	else if (res && len < ft_strlen(str))
		return (free(check), ft_concat(res, &str[len]));
	res = ft_strdup(&str[len]);
	return (free(check), remq(res));
}

char	*gest_sign(t_env *lenv, char *str, int i)
{
	char	*copy;
	char	*res;

	copy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!copy)
		return (NULL);
	ft_strncpy(copy, str, ft_strlen(str));
	while (copy[i])
	{
		if (copy[0] == 36)
		{
			res = plist(lenv, &copy[1]);
			if (!res)
				return (free(copy), "");
			return (free(copy), res);
		}
		if (copy[i] == 36 && inq(copy, i, 34))
			return (free(copy), ft_strdup(update_venv(lenv, str)));
		i++;
	}
	if (is_quoted(copy))
		return (free(copy), ft_strdup(remq(str)));
	return (free(copy), str);
}

