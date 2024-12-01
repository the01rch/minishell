/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:55:13 by kpires            #+#    #+#             */
/*   Updated: 2024/11/26 09:55:13 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

// Fonction pour gérer les commandes internes (builtins)
t_state gest_builtins(t_env *lenv, char **arr)
{
    int i;

    i = 0;
    if (ft_strncmp2(arr[0], "exit", 4)) // Vérifie si la commande est "exit"
    {
        if (arr[1])
            return (printf("exit: too many arguments\n"), ERROR); // Affiche une erreur si trop d'arguments
        printf("exit\n");
        free_arr(arr); // Libère le tableau de chaînes
        free_list(lenv); // Libère la liste des variables d'environnement
        exit(1); // Quitte le programme
    }
    if (ft_strncmp2(arr[0], "echo", 4)) // Vérifie si la commande est "echo"
    {
        i++;
        if (arr[1] && ft_strncmp2(arr[1], "-n", 2))
            i++;
        while (arr[i])
            printf("%s ", arr[i++]); // Affiche les arguments
        if (arr[1] && ft_strncmp2(arr[1], "-n", 2))
            return (VALID); // Ne pas ajouter de nouvelle ligne si l'option -n est présente
        return (printf("\n"), VALID); // Ajouter une nouvelle ligne
    }
    return (gest_env(lenv, arr)); // Gérer les autres commandes d'environnement
}