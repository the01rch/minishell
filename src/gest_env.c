/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:30:48 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/25 15:52:18 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

// Fonction pour exporter une variable d'environnement
bool	ft_export(t_env *lenv, char *str)
{
    t_env	*tmp;
    char	**arr;

    if (!str)
        return (plist(lenv, NULL), true); // Si la chaîne est NULL, afficher toutes les variables d'environnement
    tmp = lenv;
    while (tmp->next != NULL)
    {
        arr = str2arr(str, "="); // Convertir la chaîne en tableau en utilisant "=" comme séparateur
        if (!arr)
            return (false); // Si la conversion échoue, retourner false
        if (ft_strncmp2(arr[0], tmp->name, ft_strlen(arr[0])))
        {
            free(tmp->content); // Libérer l'ancien contenu
            tmp->content = ft_strdup2(arr[1]); // Dupliquer le nouveau contenu
            return (free_arr(arr), true); // Libérer le tableau et retourner true
        }
        tmp = tmp->next;
    }
    tmp->next = create_node(str); // Créer un nouveau nœud si la variable n'existe pas
    return (free_arr(arr), true); // Libérer le tableau et retourner true
}

// Fonction pour supprimer une variable d'environnement
void	ft_unset(t_env *lenv, char *str)
{
    t_env	*tmp;

    if (!str)
        return ; // Si la chaîne est NULL, ne rien faire
    tmp = lenv;
    while (tmp != NULL)
    {
        if (ft_strncmp2(str, tmp->next->name, ft_strlen(str)))
        {
            tmp->next = tmp->next->next; // Supprimer le nœud correspondant
            break ;
        }
        tmp = tmp->next;
    }
}

// Fonction pour envelopper un nom et un contenu dans une seule chaîne
char	*pwrapper(char *name, char *content, char sep)
{
    char	*dest;
    int		len;
    int		i;

    len = ft_strlen(name) + ft_strlen(content) + 1; // Calculer la longueur totale
    i = 0;
    dest = malloc(sizeof(char) * len + 1); // Allouer de la mémoire pour la nouvelle chaîne
    if (!dest)
        return (NULL); // Si l'allocation échoue, retourner NULL
    while (*name)
        dest[i++] = *name++; // Copier le nom
    dest[i++] = sep; // Ajouter le séparateur
    while (*content)
        dest[i++] = *content++; // Copier le contenu
    dest[i] = '\0'; // Terminer la chaîne
    return (dest);
}

// Fonction pour changer de répertoire
bool	ft_cd(t_env *lenv, char **arr)
{
    char	cwd[1024];

    if (!arr[1])
    {
        chdir(plist(lenv, "HOME")); // Changer de répertoire vers HOME si aucun argument n'est fourni
        ft_export(lenv, pwrapper("PWD", plist(lenv, "HOME"), '=')); // Mettre à jour la variable PWD
        return (true);
    }
    if (arr[2])
        return (printf("cd: too many arguments\n"), false); // Si trop d'arguments, afficher une erreur et retourner false
    if (chdir(arr[1]) == -1)
        return (perror("cd"), false); // Si le changement de répertoire échoue, afficher une erreur et retourner false
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_export(lenv, pwrapper("PWD", cwd, '=')); // Mettre à jour la variable PWD avec le nouveau répertoire
    else
        perror("getcwd"); // Afficher une erreur si getcwd échoue
    return (true);
}

// Fonction pour gérer les commandes d'environnement
t_state	gest_env(t_env *lenv, char **arr)
{
    if (ft_strncmp2(arr[0], "env", 3))
    {
        if (arr[1])
        {
            printf("env: '%s': No such file or directory\n", arr[1]); // Afficher une erreur si un argument est fourni
            return (ERROR);
        }
        return (plist(lenv, NULL), VALID); // Afficher toutes les variables d'environnement
    }
    if (ft_strncmp2(arr[0], "pwd", 3))
        return (printf("%s\n", plist(lenv, "PWD")), VALID); // Afficher la variable PWD
    if (ft_strncmp2(arr[0], "unset", 5))
        return (ft_unset(lenv, arr[1]), VALID); // Supprimer une variable d'environnement
    if (ft_strncmp2(arr[0], "export", 6))
        return (ft_export(lenv, arr[1]), VALID); // Exporter une variable d'environnement
    if (ft_strncmp2(arr[0], "cd", 2))
        return (ft_cd(lenv, arr), VALID); // Changer de répertoire
    return (NONE); // Retourner NONE si la commande n'est pas reconnue
}