/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:53:50 by kpires            #+#    #+#             */
/*   Updated: 2024/11/25 15:53:50 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

extern int	g_status; // Variable globale pour stocker le statut du shell

// Fonction pour obtenir le répertoire de travail actuel et le formater
static char	*get_home(t_context prompt)
{
    char	*temp;
    char	*pwd;
    char	*home;

    pwd = getcwd(NULL, 0); // Obtient le répertoire de travail actuel
    if (!pwd)
        pwd = ft_strdup("∅ "); // Si l'obtention échoue, utilise un symbole de remplacement
    home = shell_getenv("HOME", prompt.env, 4); // Obtient la variable d'environnement HOME
    if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
    {
        temp = pwd;
        pwd = ft_strjoin("~", &pwd[ft_strlen(home)]); // Remplace le chemin HOME par ~
        free(temp);
    }
    free(home);
    home = ft_strjoin(GREEN, pwd); // Ajoute la couleur verte au chemin
    free(pwd);
    pwd = ft_strjoin(home, " "); // Ajoute un espace après le chemin
    free(home);
    home = ft_strjoin(" ", pwd); // Ajoute un espace avant le chemin
    free(pwd);
    pwd = ft_strjoin(home, DEFAULT); // Ajoute la couleur par défaut après le chemin
    free(home);
    return (pwd); // Retourne le chemin formaté
}

// Fonction pour obtenir le nom de l'utilisateur actuel
static char	*get_user(t_context prompt)
{
    char	**user;
    char	*temp;

    user = NULL;
    exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.env); // Exécute la commande whoami pour obtenir le nom de l'utilisateur
    if (!user)
        user = ft_extend_matrix(user, "guest"); // Si l'obtention échoue, utilise "guest"
    temp = ft_strjoin(NULL, *user); // Concatène le nom de l'utilisateur
    ft_free_matrix(&user); // Libère la mémoire allouée pour le tableau de chaînes
    return (temp); // Retourne le nom de l'utilisateur
}

// Fonction pour générer l'invite de commande du shell
char	*shell_getprompt(t_context prompt)
{
    char	*temp;
    char	*temp2;
    char    *aux;

    temp = get_user(prompt); // Obtient le nom de l'utilisateur
    temp2 = ft_strjoin(temp, "@minishell:"); // Concatène le nom de l'utilisateur avec "@minishell:"
    free(temp);
    aux = get_home(prompt); // Obtient le répertoire de travail actuel formaté
    temp = ft_strjoin(temp2, aux); // Concatène le nom de l'utilisateur et le répertoire de travail
    free(aux);
    free(temp2);
    if (!g_status || g_status == -1)
        temp2 = ft_strjoin(temp, NULL); // Ajoute une chaîne vide si le statut est 0 ou -1
    else
        temp2 = ft_strjoin(temp, NULL); // Ajoute une chaîne vide pour les autres statuts
    free(temp);
    temp = ft_strjoin(temp2, "$> "); // Ajoute le symbole de l'invite de commande
    free(temp2);
    temp2 = ft_strjoin(temp, DEFAULT); // Ajoute la couleur par défaut après l'invite
    free(temp);
    return (temp2); // Retourne l'invite de commande complète
}