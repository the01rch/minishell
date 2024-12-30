/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:27:02 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/30 15:46:53 by redrouic         ###   ########.fr       */
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

size_t	get_env_size(t_env *lenv, char *str, size_t size)
{
	char	*res;	
	char	*test;
	size_t	j;
	size_t	n;

	j = ++size;
	n = 0;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	if (j > size)
	{
		test = malloc(sizeof(char) * (j - size) + 1);
		if (!test)
			return (printf(EALL), exit(1), size);
		ft_strncpy(test, &str[size], j - size);
		res = plist(lenv, test);
		if (res != NULL)
		{
			n = ft_strlen(res);
			(free(test), free(res));
		}
	}
	return (n);
}

/*
size_t	get_exp_size(t_env *lenv, char *arr)
{
	size_t	size;
	int		i;

	size = 0;
	while (arr[size])
	{
		if (arr[size] == 36)
			size += get_env_size(lenv, arr, size);
		else
			size++;
	}
	return (size);
}

#ifndef QUOTE
# define QUOTE

# define SINGLE 0
# define DOUBLE 1

void	expand_venv(t_env *lenv, char **arr)
{
	bool	quote[2];
	int		i;

	quote[0] = false;
	quote[1] = false;
	i = 0;
	while (*arr[i])
	{
		if (*arr[i] == 34 && !quote[SINGLE])
		{
			quote[DOUBLE] = !quote[DOUBLE];
			i++;
		}
		else if (*arr[i] == 39 && !quote[DOUBLE])
		{
			quote[SINGLE] = !quote[SINGLE];
			i++;
		}
		else if (*arr[i] == 36 && !quote[SINGLE])
			resolve_var();
		i++;
	}
}
#endif
*/
