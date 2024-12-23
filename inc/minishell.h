/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:33:18 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/24 01:38:55 by kpires           ###   ########.fr       */
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
# include <fcntl.h>
# include <errno.h>
# include <stdarg.h>
# include "struct.h"

extern int	g_signal;

/*LIB*/
int		ft_strlen(const char *str);
bool	ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *src);
char	*ft_concat(char *str, char *str2);
void	ft_strncpy(char *dst, char *src, int n);
size_t	ft_strlcat(char *dest, const char *src, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_isalnum(int c);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *p, int i, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/*UNDEFINED*/
t_state	gest_builtins(t_env *lenv, t_cmd *cmd);
bool	ft_export(t_env *lenv, char *str);
char	*plist(t_env *lenv, char *name);
void	gest_shell(t_env *lenv, t_cmd *cmd, int *std_save);
char	*update_venv(t_env *lenv, char *str);
char	*gest_sign(t_env *lenv, char *str, int i);
int		ft_exec(t_cmd cmd, t_env *list);

/*PARSING*/
bool	is_syntax_valid(char *str);
t_env	*create_node(char *str);
t_env	*arr2list(char **env);
char	**str2arr(char *str, const char *chr, bool quote);

/*UTILS*/
bool	inq(char *str, int index, char quote);
char	*remq(char *str);
bool	is_chr(const char *chr, char c);
char	*pwrapper(char *name, char *content, char sep);
int		count_rows(const char *chr, char *str, bool quote);
int		skip_spaces(char *str);
int		check_quotes(char *str, int i);

/*FREE*/
void	free_node(t_env *node);
void	free_arr(char **arr);
void	free_list(t_env *list);
void	free_cmd(t_cmd *cmd);

/*REDIR*/
int		ft_redir(t_cmd *cmd, t_env *lenv);
int		ft_overwrite(t_cmd *cmd, char *redir);
int		ft_append(t_cmd *cmd, char *redir);
int		ft_redirect_input(t_cmd *cmd, char *redir);
int		ft_heredoc(t_cmd *cmd, char *redir, t_env *lenv);
int		dup_inf_out(t_cmd *cmd, int *std_save);
int		close_fd(t_cmd *cmd, int *std_save, bool is_error);
int		ft_hd_nq(t_cmd *cmd, int *fd, char *del, t_env *lenv);
int		ft_hd_q(t_cmd *cmd, int *fd, char *del);
ssize_t	write_here(const void *buffer, int fd, size_t count);
int		extract_varlen(char *line, int len, char **v_name, bool del_sign);
#endif
