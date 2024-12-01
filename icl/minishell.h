/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:33:18 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/29 14:54:23 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "../get_next_line/inc/get_next_line.h"

# define READ_END 0
# define WRITE_END 1
# define GREEN "\001\033[1;92m\002"
# define DEFAULT "\001\033[0;39m\002"

typedef enum state
{
	NONE,
	VALID,
	ERROR,	
}	t_state;


typedef struct s_context
{
	t_list *cmds; // Liste chaînée des commandes à exécuter
	char **env; // Environnement
	pid_t pid; // PID du processus
} t_context;

typedef struct s_cmd_info
{
	char **full_cmd; // Commande complète
	char *full_path; // Chemin complet de la commande
	int infile; // Descripteur de fichier d'entrée
	int outfile; // Descripteur de fichier de sortie
}		t_cmd_info;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUP_ERR = 7,
	FORK_ERR = 8,
	PIPE_ERR = 9,
	PIPEND_ERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

t_env	*arr2list(char **arr, int len);
t_env	*create_node(char *str);
t_state	gest_env(t_env *lenv, char **arr);
t_state	gest_builtins(t_env *len, char **arr);
char	*plist(t_env *lenv, char *name);
void	free_list(t_env *list);
// int		ft_strlen(const char *str);
// bool	ft_strncmp(char *s1, char *s2, int n);
// char	*ft_strdup(char *src);
void free_arr(char **arr);
char	**str2arr(char *str, const char *charset);
void	free_arr(char **arr);
char	*pwrapper(char *name, char *content, char sep);
void	gest_shell(t_env *lenv, char **arr);
t_state gest_builtins(t_env *lenv, char **arr);
void	*shell_perror(int err_type, char *param, int err);
char    *shell_getenv(char *var, char **env, int n);
char    **shell_setenv(char *var, char *value, char **env, int n);
bool	ft_strncmp2(char *s1, char *s2, int n);
char	*ft_strdup2(char *src);

char	*shell_getprompt(t_context prompt);
void	exec_custom(char ***out, char *full, char *args, char **envp);

void	handle_sigint(int sig);
void	*check_args(char *out, t_context *p);
char	**ft_split_quotes(char const *str, char *set);
#endif
