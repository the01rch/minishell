/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:34:17 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/22 03:48:29 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

// Fonction pour vérifier l'accès à une commande dans les chemins spécifiés par PATH
char	*check_access(t_env *lenv, char **arr)
{
    char	**tab;
    int		i;	

    tab = str2arr(plist(lenv, "PATH"), ":"); // Convertir la variable PATH en tableau de chemins
    i = 0;
    if (!tab)
        return (NULL); // Si la conversion échoue, retourner NULL
    while (i < 7)
    {
        // Vérifier si le fichier existe et est exécutable
        if (access(pwrapper(tab[i], arr[0], '/'), F_OK) == 0
            && access(pwrapper(tab[i], arr[0], '/'), X_OK) == 0)
            return (pwrapper(tab[i], arr[0], '/')); // Retourner le chemin complet si la commande est trouvée
        i++;
    }
    return (NULL); // Retourner NULL si la commande n'est pas trouvée
}

// Fonction pour convertir une liste chaînée d'environnement en tableau de chaînes
char	**list2arr(t_env *lenv)
{
    t_env	*tmp;
    char	**arr;
    int		i;

    i = 0;
    tmp = lenv;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    arr = malloc(sizeof(char *) * (i + 1)); // Allouer de la mémoire pour le tableau
    if (!arr)
        return (NULL); // Si l'allocation échoue, retourner NULL
    i = 0;
    tmp = lenv; // Réinitialiser tmp pour parcourir la liste à nouveau
    while (tmp)
    {
        arr[i] = pwrapper(tmp->name, tmp->content, '='); // Envelopper le nom et le contenu dans une chaîne
        i++;
        tmp = tmp->next;
    }
    arr[i] = NULL; // Terminer le tableau par NULL
    return (arr);
}

// Fonction pour gérer l'exécution des commandes dans le shell
void	gest_shell(t_env *lenv, char **arr)
{
    char	*path;
    pid_t	pid;

    path = check_access(lenv, arr); // Vérifier l'accès à la commande
    pid = fork(); // Créer un processus enfant
    if (pid < 0)
        return (perror("fork failed"), exit(0), (void)0); // Si la création du processus échoue, afficher une erreur et quitter
    else if (pid == 0)
    {
        if (!path)
        {
            printf("%s: Command not found.\n", arr[0]); // Si la commande n'est pas trouvée, afficher une erreur
            exit(0);
        }
        execve(path, arr, list2arr(lenv)); // Exécuter la commande avec les variables d'environnement
    }
    if (pid > 0)
        wait(NULL); // Attendre la fin du processus enfant
}