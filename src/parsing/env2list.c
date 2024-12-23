/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:59:11 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/23 11:02:14 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*create_node(char *str)
{
	t_env	*new;
	char	**arr;

	if (!str)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	arr = str2arr(str, "=", false);
	if (!arr)
		return (free_arr(arr), free(new), NULL);
	new->name = ft_strdup(arr[0]);
	new->content = ft_strdup(arr[1]);
	new->next = NULL;
	if (!new->name || (arr[1] && !new->content))
		return (free_arr(arr), free_node(new), NULL);
	free_arr(arr);
	return (new);
}

t_env	*arr2list(char **env)
{
	t_env	*head;
	t_env	*tmp;
	t_env	*result;

	if (!*env)
		return (NULL);
	head = create_node("a=b");
	if (!head)
		return (NULL);
	tmp = head;
	while (*env)
	{
		tmp->next = create_node(*env);
		if (!tmp->next)
			return (free_list(head), NULL);
		tmp = tmp->next;
		env++;
	}
	result = head->next;
	free_node(head);
	return (result);
}

char	*plist(t_env *lenv, char *name)
{
	t_env	*tmp;
	char	*result;

	tmp = lenv;
	while (tmp != NULL)
	{
		if (name && ft_strcmp(name, tmp->name))
		{
			result = ft_strdup(tmp->content);
			return (result);
		}
		else if (!name)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
