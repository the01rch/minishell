/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/29 14:58:31 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

extern int	g_status; // Variable globale pour stocker le statut du shell

// Fonction pour obtenir le PID du shell
static void shell_getpid(t_context *p)
{
    pid_t pid;

    pid = fork(); // Crée un processus enfant
    printf("pid: %d\n", pid);
    if (pid < 0) // Vérifie si le fork a échoué
    {
        shell_perror(FORK_ERR, NULL, 1); // Affiche une erreur
        ft_free_matrix(&p->env); // Libère la mémoire allouée pour l'environnement
        exit(1); // Quitte le programme
    }
    if (!pid) // Si c'est le processus enfant
    {
        ft_free_matrix(&p->env); // Libère la mémoire allouée pour l'environnement
        exit(1); // Quitte le programme
    }
    waitpid(pid, NULL, 0); // Attend la fin du processus enfant
    p->pid = pid - 1; // Stocke le PID du shell
}

// Fonction pour initialiser les variables du shell
static t_context init_vars(t_context prompt, char *str, char **av)
{
    char *shlvl;

    str = getcwd(NULL, 0); // Obtient le répertoire de travail actuel
    prompt.env = shell_setenv("PWD", str, prompt.env, 3); // Définit la variable d'environnement PWD
    free(str);
    str = shell_getenv("SHLVL", prompt.env, 5); // Obtient la variable d'environnement SHLVL
    if (!str || ft_atoi(str) <= 0)
        shlvl = ft_strdup("1"); // Définit SHLVL à 1 si elle n'existe pas ou est invalide
    else
        shlvl = ft_itoa(ft_atoi(str) + 1); // Incrémente SHLVL
    free(str);
    prompt.env = shell_setenv("SHLVL", shlvl, prompt.env, 5); // Met à jour SHLVL
    free(shlvl);
    str = shell_getenv("PATH", prompt.env, 4); // Obtient la variable d'environnement PATH
    if (!str)
        prompt.env = shell_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.env, 4); // Définit PATH si elle n'existe pas
    free(str);
    str = shell_getenv("_", prompt.env, 1); // Obtient la variable d'environnement _
    if (!str)
        prompt.env = shell_setenv("_", av[0], prompt.env, 1); // Définit _ si elle n'existe pas
    free(str);
    return (prompt);
}

// Fonction pour initialiser le contexte du shell
static t_context init_prompt(char **av, char **env)
{
    t_context prompt;
    char *str;

    str = NULL;
    prompt.cmds = NULL;
    prompt.env = ft_dup_matrix(env); // Duplique l'environnement
    g_status = 0; // Initialise le statut global
    shell_getpid(&prompt); // Obtient le PID du shell
    prompt = init_vars(prompt, str, av); // Initialise les variables du shell
    return (prompt);
}

// Fonction principale du programme
// int main(int ac, char **av, char **env)
// {
//     t_context prompt;
//     char *str;
//     char *out;
    
//     prompt = init_prompt(av, env); // Initialise le contexte du shell
//     while (ac && av)
//     {
//         signal(SIGINT, handle_sigint); // Gère le signal SIGINT
//         signal(SIGQUIT, SIG_IGN); // Ignore le signal SIGQUIT
//         str = shell_getprompt(prompt); // Obtient l'invite de commande
//         if (str)
//             out = readline(str); // Lit l'entrée de l'utilisateur
//         else
//             out = readline("guest@minishell: $> ");
//         free(str);
//         if (!check_args(out, &prompt)) // Vérifie les arguments
//             break;
//     }
//     exit(g_status); // Quitte le programme avec le statut global
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av, char **env) {

    t_context prompt;
    (void)ac;
        
    prompt = init_prompt(av, env);
    (void)prompt;
    int i = 0;
    
    char **result_ft_cmdtrim = ft_split_quotes(av[1], " ");
    (void)result_ft_cmdtrim;
    printf("ft_cmdtrim result:");
    while (result_ft_cmdtrim[i]) {
        printf("\"%s\",", result_ft_cmdtrim[i]);
        i++;
    }

    return 0;
}