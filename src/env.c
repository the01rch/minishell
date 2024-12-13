/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:02:31 by kpires            #+#    #+#             */
/*   Updated: 2024/12/13 16:04:19 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

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
