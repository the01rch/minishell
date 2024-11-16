/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:25:21 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/16 02:23:48 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

static bool is_charset(const char *chr, char c)
{
	while (*chr)
	{
		if (c == *chr)
			return (true);
		chr++;
	}
	return (false);
}

static int	count_rows(const char *chr, char *str)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while (is_charset(chr, *str))
		str++;
	while (str[i])
	{
		if (is_charset(chr, str[i]) 
				&& !is_charset(chr, str[i + 1]) && str[i + 1])
			rows++;
		i++;
	}
	return (rows + 1);
}

static int	*count_cols(const char *chr, char *str, int rows)
{
	int	*cols;
	int	y;
	int	x;

	if (rows == 0)
		return (0);
	cols = malloc(sizeof(int) * rows);
	if (!cols)
		return (0);
	y = 0;
	x = 0;
	while (*str)
	{
		if (!is_charset(chr, *str) && *str != '\0')
			x++;
		if (x > 0 && is_charset(chr, *str))
		{
			cols[y++] = x;
			x = 0;
		}
		str++;
	}
	cols[y] = x;
	return (cols);
}

static char	**init_arr(const char *chr, char *str)
{
	char	**arr;
	int		*cols;
	int		rows;
	int		y;
	int		x;

	rows = count_rows(chr, str);
	cols = count_cols(chr, str, rows);
	if (!cols)
		return (0);
	arr = malloc(sizeof(char *) * (rows + 1));
	if (!arr)
		return (0);
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
	free(cols);
	return (arr);
}

char	**str2arr(char *str, const char *chr)
{
	char	**arr;
	int		y;
	int		x;
	int		i;

	arr = init_arr(chr, str);
	if (!arr)
		return (0);
	x = 0;
	y = 0;
	i = 0;
	while (str[i])
	{
		if (!is_charset(chr, str[i]) && str[i] != '\0')
			arr[y][x++] = str[i];
		if (x > 0 && is_charset(chr, str[i]))
		{
			arr[y++][x] = '\0';
			x = 0;
		}
		i++;
	}
	arr[y + 1] = 0;
	return (arr);
}
