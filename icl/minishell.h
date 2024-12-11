/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:33:18 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/10 18:25:31 by redrouic         ###   ########.fr       */
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
}	t_state;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

int		ft_strlen(const char *str);
bool	ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);
char	*ft_concat(char *str, char *str2);
void	ft_strncpy(char *dst, char *src, int n);
t_env	*arr2list(char **env);
t_env	*create_node(char *str);
t_state	gest_env(t_env *lenv, char **arr);
t_state	gest_builtins(t_env *len, char **arr);
char	*plist(t_env *lenv, char *name);
void	free_list(t_env *list);
char	**str2arr(char *str, const char *chr, bool quote);
void	free_arr(char **arr);
char	*pwrapper(char *name, char *content, char sep);
void	gest_shell(t_env *lenv, char **arr);
bool	inQ(char *str, int index, char quote);
char	*gest_sign(t_env *lenv, char *str);

#endif
