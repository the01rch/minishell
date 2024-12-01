/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+           */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:59:11 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/21 16:34:15 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

// Fonction pour créer un nouveau nœud de la liste chaînée
t_env	*create_node(char *str)
{
    t_env	*new;
    char	**arr;

    new = (t_env *)malloc(sizeof(t_env)); // Allouer de la mémoire pour le nouveau nœud
    if (!new)
        exit(1); // Si l'allocation échoue, quitter le programme
    arr = str2arr(str, "="); // Convertir la chaîne en tableau en utilisant "=" comme séparateur
    if (!arr)
        exit(1); // Si la conversion échoue, quitter le programme
    new->name = ft_strdup2(arr[0]); // Dupliquer le nom
    new->content = ft_strdup2(arr[1]); // Dupliquer le contenu
    new->next = NULL; // Initialiser le pointeur suivant à NULL
    return (new);
}

// Fonction pour convertir un tableau de chaînes en liste chaînée
t_env	*arr2list(char **arr, int len)
{
    t_env	*head;
    t_env	*tmp;
    int		i;

    i = 0;
    if (len == 0)
        return (NULL); // Si la longueur est 0, retourner NULL
    head = create_node("a=b"); // Créer un nœud de tête fictif
    tmp = head;
    while (i < len)
    {
        tmp->next = create_node(arr[i]); // Créer un nouveau nœud pour chaque élément du tableau
        tmp = tmp->next;
        i++;
    }
    return (head->next); // Retourner le premier nœud réel
}

// Fonction pour afficher ou retourner le contenu d'une variable d'environnement
char	*plist(t_env *lenv, char *name)
{
    t_env	*tmp;

    tmp = lenv;
    while (tmp != NULL)
    {
        if (name && ft_strncmp2(name, tmp->name, ft_strlen(name)))
            return (ft_strdup2(tmp->content)); // Si le nom correspond, retourner une copie du contenu
        else if (!name)
            printf("%s=%s\n", tmp->name, tmp->content); // Si aucun nom n'est fourni, afficher toutes les variables avec le préfixe export
        tmp = tmp->next;
    }
    return (NULL); // Retourner NULL si la variable n'est pas trouvée
}

// Fonction pour libérer la mémoire allouée pour la liste chaînée
void	free_list(t_env *list)
{
    t_env	*tmp;

    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->name); // Libérer le nom
        free(tmp->content); // Libérer le contenu
        free(tmp); // Libérer le nœud
    }
}