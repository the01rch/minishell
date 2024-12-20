/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:33:18 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/20 20:31:01 by redrouic         ###   ########.fr       */
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
# include "struct.h"

int		ft_strlen(const char *str);
bool	ft_strcmp(char *s1, char *s2);
bool	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *src);
char	*ft_concat(char *str, char *str2);
void	ft_strncpy(char *dst, char *src, int n);
t_env	*arr2list(char **env);
t_env	*create_node(char *str);
t_state	gest_env(t_env *lenv, char **arr);
t_state	gest_builtins(t_env *lenv, t_cmd *cmd);
char	*plist(t_env *lenv, char *name);
void	free_list(t_env *list);
char	**str2arr(char *str, const char *chr, bool quote);
void	free_arr(char **arr);
char	*pwrapper(char *name, char *content, char sep);
void	gest_shell(t_env *lenv, t_cmd *cmd);
bool	inq(char *str, int index, char quote);
char	*gest_sign(t_env *lenv, char *str, int i);
t_state	ft_redir(t_global *global);
int		count_rows(const char *chr, char *str, bool quote);
void	free_arr(char **arr);
void	listening(void);
char	*update_venv(t_env *lenv, char *str);
char	*remq(char *str);
//void	free_global(t_global *global);
void	free_node(t_env *node);
bool	is_chr(const char *chr, char c);
bool	is_syntax_valid(char *str);

#endif
