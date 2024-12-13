/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:25:21 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/13 17:45:03 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

static bool	is_charset(const char *chr, char c)
{
	while (*chr)
	{
		if (c == *chr)
			return (true);
		chr++;
	}
	return (false);
}

int	count_rows(const char *chr, char *str, bool quote)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while (is_charset(chr, str[i]))
		i++;
	while (str[i])
	{
		if ((!quote && str[i + 1] && is_charset(chr, str[i])
				&& !is_charset(chr, str[i + 1])) || (quote && str[i + 1]
				&& is_charset(chr, str[i]) && !is_charset(chr, str[i + 1])
				&& !inq(str, i, 0)))
			rows++;
		i++;
	}
	return (rows + 1);
}

static int	*count_cols(const char *chr, char *str, int rows, bool quote)
{
	int	*cols;
	int	vec[2];
	int	i;

	cols = malloc(sizeof(int) * (rows + 1));
	if (!cols)
		return (0);
	vec[0] = 0;
	vec[1] = 0;
	i = 0;
	while (str[i])
	{
		if ((!is_charset(chr, str[i]) && str[i])
			|| (quote && is_charset(chr, str[i]) && inq(str, i, 0)))
			vec[0]++;
		if ((!quote && vec[0] > 0 && is_charset(chr, str[i])) || (quote
				&& vec[0] > 0 && is_charset(chr, str[i]) && !inq(str, i, 0)))
		{
			cols[vec[1]++] = vec[0];
			vec[0] = 0;
		}
		i++;
	}
	cols[vec[1]] = vec[0];
	return (cols);
}

static char	**init_arr(const char *chr, char *str, bool quote)
{
	char	**arr;
	int		*cols;
	int		rows;
	int		y;
	int		x;

	rows = count_rows(chr, str, quote);
	cols = count_cols(chr, str, rows, quote);
	if (!cols)
		return (NULL);
	arr = malloc(sizeof(char *) * (rows + 1));
	if (!arr)
		return (free(cols), NULL);
	y = 0;
	x = 0;
	while (y < rows)
	{
		arr[y] = malloc(sizeof(char) * (cols[y] + 1));
		while (x <= cols[y])
			arr[y][x++] = '\0';
		x = 0;
		y++;
	}
	arr[y] = NULL;
	return (free(cols), arr);
}

char	**str2arr(char *str, const char *chr, bool quote)
{
	char	**arr;
	int		vec[2];
	int		i;

	arr = init_arr(chr, str, quote);
	if (!arr)
		return (0);
	vec[0] = 0;
	vec[1] = 0;
	i = 0;
	while (str[i])
	{
		if ((!is_charset(chr, str[i]) && str[i])
			|| (quote && is_charset(chr, str[i]) && inq(str, i, 0)))
			arr[vec[1]][vec[0]++] = str[i];
		if ((!quote && vec[0] > 0 && is_charset(chr, str[i])) || (quote
				&& vec[0] > 0 && is_charset(chr, str[i]) && !inq(str, i, 0)))
		{
			arr[vec[1]++][vec[0]] = '\0';
			vec[0] = 0;
		}
		i++;
	}
	return (arr);
}
