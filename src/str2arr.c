/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:25:21 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/06 22:06:42 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

static int	count_rows(char *str)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while (*str == ' ')
		str++;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0')
			rows++;
		i++;
	}
	return (rows + 1);
}

static int	*count_cols(char *str, int rows)
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
		if (*str != ' ' && *str != '\0')
			x++;
		if (x > 0 && *str == ' ')
		{
			cols[y++] = x;
			x = 0;
		}
		str++;
	}
	cols[y] = x;
	return (cols);
}

static char	**init_arr(char *str)
{
	char	**arr;
	int		*cols;
	int		rows;
	int		y;
	int		x;

	rows = count_rows(str);
	cols = count_cols(str, rows);
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

char	**str2arr(char *str)
{
	char	**arr;
	int		y;
	int		x;
	int		i;

	arr = init_arr(str);
	if (!arr)
		return (0);
	x = 0;
	y = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\0')
			arr[y][x++] = str[i];
		if (x > 0 && str[i] == ' ')
		{
			arr[y++][x] = '\0';
			x = 0;
		}
		i++;
	}
	arr[y + 1] = 0;
	return (arr);
}
