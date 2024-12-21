/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:30:48 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/21 00:50:26 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

bool	ft_export(t_env *lenv, char *str)
{
	t_env	*tmp;
	char	**arr;

	tmp = lenv;
	while (tmp->next != NULL)
	{
		arr = str2arr(str, "=", false);
		if (!arr)
			return (false);
		if (ft_strcmp(arr[0], tmp->name))
		{
			free(tmp->content);
			tmp->content = ft_strdup(arr[1]);
			return (free_arr(arr), true);
		}
		tmp = tmp->next;
	}
	tmp->next = create_node(str);
	return (free_arr(arr), true);
}

void	ft_unset(t_env *lenv, char *str)
{
	t_env	*tmp;
	t_env	*to_delete;

	if (!lenv || !str)
		return ;
	if (ft_strcmp(str, lenv->name))
	{
		to_delete = lenv;
		lenv = lenv->next;
		free_node(to_delete);
		return ;
	}
	tmp = lenv;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(str, tmp->next->name))
		{
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			free_node(to_delete);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*pwrapper(char *name, char *content, char sep)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen(name) + ft_strlen(content) + 1;
	i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (*name)
		dest[i++] = *name++;
	dest[i++] = sep;
	while (*content)
		dest[i++] = *content++;
	dest[i] = '\0';
	return (dest);
}

bool	ft_cd(t_env *lenv, char **arr)
{
	char	cwd[1024];

	if (!arr[1])
	{
		chdir(plist(lenv, "HOME"));
		ft_export(lenv, pwrapper("PWD", plist(lenv, "HOME"), '='));
		return (true);
	}
	if (arr[2])
		return (printf("cd: too many arguments\n"), false);
	if (chdir(arr[1]) == -1)
		return (perror("cd"), false);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_export(lenv, pwrapper("PWD", cwd, '='));
	else
		perror("getcwd");
	return (true);
}

t_state	gest_env(t_env *lenv, char **arr)
{
	char	*result;

	if (ft_strcmp(arr[0], "env"))
	{
		if (arr[1])
			return (printf(EENV, arr[1]), ERROR);
		return (plist(lenv, NULL), VALID);
	}
	if (ft_strcmp(arr[0], "pwd"))
	{
		result = plist(lenv, "PWD");
		if (result)
		{
			printf("%s\n", result);
			free(result);
		}
		return (VALID);
	}
	if (ft_strcmp(arr[0], "unset"))
		return (ft_unset(lenv, arr[1]), VALID);
	if (ft_strcmp(arr[0], "export"))
		return (ft_export(lenv, arr[1]), VALID);
	if (ft_strcmp(arr[0], "cd"))
		return (ft_cd(lenv, arr), VALID);
	return (NONE);
}
