/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:56 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/25 17:29:22 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

extern int	g_status;


static void shell_getpid(t_context *p)
{
    pid_t   pid;

    pid = fork();
    printf("pid: %d\n", pid);
    if (pid < 0)
    {
        shell_perror(FORK_ERR, NULL, 1);
        ft_free_matrix(&p->env);
        exit(1);
    }
    if(!pid)
    {
        ft_free_matrix(&p->env);
        exit(1);
    }
    waitpid(pid, NULL, 0);
    p->pid = pid - 1;
}

static t_context init_vars(t_context prompt, char *str, char **en)
{
    char    *num;

    str = getcwd(NULL, 0);
    prompt.env = shell_setenv("PWD", str, prompt.env, 3);
    free(str);
    str = shell_getenv("SHLVL", prompt.env, 5);
    if (!str || ft_atoi(str) <= 0)
        num = ft_strdup("1");
    else
        num = ft_itoa(ft_atoi(str) + 1);
    free(str);
    prompt.env = shell_setenv("SHLVL", num, prompt.env, 5);
    free(num);
    str = shell_getenv("PATH", prompt.env, 4);
    if (!str)
        prompt.env = shell_setenv("PATH", \
        "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.env, 4);
    free(str);
    str = shell_getenv("_", prompt.env, 1);
    if (!str)
        prompt.env = shell_setenv("_", en[0], prompt.env, 1);
    free(str);
    return (prompt);
}

// Fonction pour libérer la mémoire allouée pour un tableau de chaînes
void	free_arr(char **arr)
{
    int	i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Fonction pour gérer les commandes internes (builtins)
t_state	gest_builtins(t_env *lenv, char **arr)
{
    int	i;

    i = 0;
    if (ft_strncmp2(arr[0], "exit", 4))
    {
        if (arr[1])
            return (printf("exit: too many arguments\n"), ERROR); // Afficher une erreur si trop d'arguments
        printf("exit\n");
        free_arr(arr);
        free_list(lenv);
        exit(1); // Quitter le programme
    }
    if (ft_strncmp2(arr[0], "echo", 4))
    {
        i++;
        if (arr[1] && ft_strncmp2(arr[1], "-n", 2))
            i++;
        while (arr[i])
            printf("%s ", arr[i++]); // Afficher les arguments
        if (arr[1] && ft_strncmp2(arr[1], "-n", 2))
            return (VALID); // Ne pas ajouter de nouvelle ligne si l'option -n est présente
        return (printf("\n"), VALID); // Ajouter une nouvelle ligne
    }
    return (gest_env(lenv, arr)); // Gérer les autres commandes d'environnement
}

static t_context init_prompt(char **av, char **env)
{
    t_context    prompt;
    char    *str;

    str = NULL;
    prompt.cmds = NULL;
    prompt.env = ft_dup_matrix(env);
    g_status = 0;
    shell_getpid(&prompt);
    prompt = init_vars(prompt, str, av);
    return (prompt);
}

// Fonction principale
int	main(int ac, char **av, char **env)
{
    t_context prompt;
    char	*str;
    char	*out;
    
    prompt = init_prompt(av, env);
    while (ac && av)
    {
        signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = shell_getprompt(prompt);
        if(str)
            out = readline(str);
        else
            out = readline("guest@minishell $ ");
        free(str);
        if (!check_args(out, &prompt))
			break ;
    }
    exit(g_status);
}