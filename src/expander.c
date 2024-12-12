/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:27:02 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/12 15:36:12 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

bool	is_unclosed(char *str)
{
	char	openQ;
	int		i;

	openQ = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39) 
		{
			if (openQ == 0) 
				openQ = str[i];
			else if (str[i] == openQ) 
				openQ = 0;
		}
		i++;
	}
	return (openQ == 0);
}

bool	inQ(char *str, int index, char quote)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (quote != 0 && str[i] == quote) 
			return (true);
		else if (quote == 0 && (str[i] == 34 || str[i] == 39))
			return (true);
		i--;
	}
	return (false);
}

static char	*remQ(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str)));
	while (str[i])
	{
		if ((str[i] != 34 && !inQ(str, i, 0)) 
			&& (str[i] != 39 && !inQ(str, i, 0)))
			res[j++] = str[i];
		i++;
	}
	res[j] = 0;
	return (res);
}

static char	*update_venv(t_env *lenv, char *str)
{
	char	*check;
	char	*res;
	int		len;

	len = 0;
	while (str[len] && str[len] != 32)
		len++;
	check = malloc(sizeof(char) * len + 1);
	ft_strncpy(check, str, len);
	if (inQ(check, 1, 0))
		check = ft_strdup(remQ(check));
	res = plist(lenv, &check[1]);
	if (res && len == ft_strlen(str))
		return (free(check), res);
	else if (res && len < ft_strlen(str))
		return (free(check), ft_concat(res, &str[len]));
	res = ft_strdup(&str[len]);
	return (free(check), remQ(res));
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

char	*gest_sign(t_env *lenv, char *str)
{
	char	copy[ft_strlen(str)];
	char	*res;
	int		i;

	i = 0;
	ft_strncpy(copy, str, ft_strlen(str));
	if (is_quoted(copy) && !is_unclosed(copy))
		return ("");
	while (copy[i])
	{
		if (copy[0] == 36)
		{
			res = plist(lenv, &copy[1]);
			if (!res)
				return ("");
			return (ft_strdup(res));	
		}
		if (copy[i] == 36 && inQ(copy, i, 34))
			return (ft_strdup(update_venv(lenv, copy)));
		i++;
	}
	if (is_quoted(copy))
		return (ft_strdup(remQ(copy)));
	return (str);
}
