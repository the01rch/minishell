/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:33:18 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/13 17:16:08 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/wait.h>

typedef enum state
{
	NONE,
	VALID,
	ERROR,
	SQUOTE,
	DQUOTE,
	REDIR,
	APPREDIR,
	HEREDOC,
	PIPE,
}	t_state;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_command
{
	char	*exec;
	char	*args;
	char	*full;
	int		infile;
	int		outfile;
	int		fd[2];
}	t_command;

typedef struct s_global
{
	char		**env;
	char		**argv;
	char		**full;
	t_env		*env_list;
	pid_t		pid;
	t_command	**cmds;
}	t_global;

int		ft_strlen(const char *str);
bool	ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);
char	*ft_concat(char *str, char *str2);
void	ft_strncpy(char *dst, char *src, int n);
t_env	*arr2list(char **env);
t_env	*create_node(char *str);
t_state	gest_env(t_env *lenv, char **arr);
t_state	gest_builtins(t_env *lenv, char **arr);
char	*plist(t_env *lenv, char *name);
void	free_list(t_env *list);
char	**str2arr(char *str, const char *chr, bool quote);
void	free_arr(char **arr);
char	*pwrapper(char *name, char *content, char sep);
void	gest_shell(t_env *lenv, char **arr);
bool	inq(char *str, int index, char quote);
char	*gest_sign(t_env *lenv, char *str, int i);
t_state	ft_redir(t_global *global);
int		count_rows(const char *chr, char *str, bool quote);
void	free_arr(char **arr);
void	listening(void);
void	free_cmds(t_command **cmds);
char	*update_venv(t_env *lenv, char *str);
char	*remq(char *str);
void	free_global(t_global *global);
#endif
