/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:30:48 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/18 22:26:43 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

int	arr_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

t_env	*create_node(char *str)
{
	t_env	*new;
	char	**arr;

	new = (t_env*)malloc(sizeof(t_env));
	if (!new)
		exit(1);
	arr = str2arr(str, "=");
	if (!arr)
		exit(1);
	new->name = ft_strdup(arr[0]);
	new->content = ft_strdup(arr[1]);
	new->next = NULL;
	//free_arr(arr);
	return (new);
}

t_env	*arr2list(char **arr, int len)
{
	t_env	*head;
	t_env	*tmp;
	int		i;

	i = 0;
	if (len == 0)
		return (NULL);
	head = create_node("a=b");
	tmp = head;
	while (i < len)
	{
		tmp->next = create_node(arr[i]);
		tmp = tmp->next;
		i++;
	}
	return (head->next);
}

void	print_list(t_env *lenv, char *name)
{
	t_env	*tmp;

	tmp = lenv;
	while (tmp != NULL)
	{
		if (name && ft_strncmp(name, tmp->name, 3))
		{
			printf("%s\n", tmp->content);
			break ;
		}
		else if (!name)
			printf("%s=%s\n", tmp->name, tmp->content);	
		tmp = tmp->next;
	}
}

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

char	*path_wrapper(char *name, char *content)
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
	dest[i++] = 61;
	while (*content)
		dest[i++] = *content++;
	dest[i] = '\0';
	return (dest);
}

bool	gest_env(t_env *lenv, char **arr)
{
	char	cwd[1024];

	if (ft_strncmp(arr[0], "env", 3))
		return (print_list(lenv, NULL), true);
	if (ft_strncmp(arr[0], "pwd", 3))
		return (print_list(lenv,  "PWD"), true);
	if (ft_strncmp(arr[0], "unset", 5))
		return (ft_unset(lenv, arr[1]), true);
	if (ft_strncmp(arr[0], "export", 6))
		return (ft_export(lenv, arr[1]), true);
	if (ft_strncmp(arr[0], "cd", 2))
	{
		if (!arr[1])
			return (chdir(getenv("HOME")), true);
		if (chdir(arr[1]) == -1)
			return (perror("cd"), false);
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_export(lenv, path_wrapper("PWD", cwd));
		else
			perror("getcwd");
		return (true);
	}
	return (gest_builtins(arr));
}
