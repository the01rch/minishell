/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:59:11 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/25 18:36:18 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

t_env	*create_node(char *str)
{
	t_env	*new;
	char	**arr;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		exit(1);
	arr = str2arr(str, "=");
	if (!arr)
		exit(1);
	new->name = ft_strdup(arr[0]);
	new->content = ft_strdup(arr[1]);
	new->next = NULL;
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

char	*plist(t_env *lenv, char *name)
{
	t_env	*tmp;

	tmp = lenv;
	while (tmp != NULL)
	{
		if (name && ft_strcmp(name, tmp->name))
			return (ft_strdup(tmp->content));
		else if (!name)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_list(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
}
