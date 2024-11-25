/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:30:48 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/25 11:05:24 by redrouic         ###   ########.fr       */
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
		arr = str2arr(str, "=");
		if (!arr)
			return (false);
		if (ft_strncmp(arr[0], tmp->name, ft_strlen(arr[0])))
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

	tmp = lenv;
	while (tmp != NULL)
	{
		if (ft_strncmp(str, tmp->next->name, ft_strlen(str)))
		{
			tmp->next = tmp->next->next;
			break ;
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
	dest = malloc(sizeof(char) * len + 1);
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
	if (ft_strncmp(arr[0], "env", 3))
	{
		if (arr[1])
		{
			printf("env: '%s': No such file or directory\n", arr[1]);
			return (ERROR);
		}
		return (plist(lenv, NULL), VALID);
	}
	if (ft_strncmp(arr[0], "pwd", 3))
		return (printf("%s\n", plist(lenv, "PWD")), VALID);
	if (ft_strncmp(arr[0], "unset", 5))
		return (ft_unset(lenv, arr[1]), VALID);
	if (ft_strncmp(arr[0], "export", 6))
		return (ft_export(lenv, arr[1]), VALID);
	if (ft_strncmp(arr[0], "cd", 2))
		return (ft_cd(lenv, arr), VALID);
	return (NONE);
}
