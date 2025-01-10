/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:33:18 by redrouic          #+#    #+#             */
/*   Updated: 2025/01/10 02:36:15 by redrouic         ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include "struct.h"

extern int	g_signal;

/*LIB*/
int		ft_strlen(const char *str);
bool	ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *src);
void	ft_strncpy(char *dst, char *src, int n);
size_t	ft_strlcat(char *dest, const char *src, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_isalnum(int c);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *p, int i, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_is_nb(char *cmd);
char	*ft_itoa(int n);
void	ft_perror(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*BUILTINS*/
t_state	gest_builtins(t_global *g, t_cmd *cmd);
int		ft_exit(t_global *g, t_cmd *cmd, bool print);
bool	ft_export(t_global *g, char **str, bool multiples);

/*SIGNAL*/
void	signal_ctrd(t_global *g);

/*EXEC*/
void	execve_cmd(t_global *g, int id);
int		set_check_cmd(t_global *g, int id);
int		exec_cmd(t_global *g, int id);
void	close_all_fd_child(t_global *g);
int		ft_exec(t_global *g);
void	exec_cmds(t_global *g);
void	ft_waitall(t_global *g);

/*PARSING*/
bool	is_syntax_valid(t_global *g, char *str);
t_env	*create_node(char *str);
t_env	*arr2list(char **env);
char	**list2arr(t_env *lenv);
char	**str2arr(char *str, const char *chr, bool quote);
void	init_s_cmd(t_global *g, char *line);
char	*gest_expand(t_global *g, char *str);

/*UTILS*/
bool	inq(char *str, int index, char quote);
char	*remq(char *str);
bool	is_chr(const char *chr, char c);
char	*pwrapper(char *name, char *content, char sep);
int		count_rows(const char *chr, char *str, bool quote);
int		skip_spaces(char *str);
int		check_quotes(char *str, int i);
char	*plist(t_env *lenv, char *name);

/*FREE*/
void	free_node(t_env *node);
void	free_arr(char **arr);
void	free_list(t_env *list);
void	free_cmds(t_global *g);
void	free_cmd(t_cmd *cmd);

/*REDIR*/
int		ft_redir(t_global *g, t_env *lenv, int i, int tmp);
int		ft_overwrite(t_global *g, t_cmd *cmd, char *redir);
int		ft_append(t_global *g, t_cmd *cmd, char *redir);
int		ft_redir_input(t_global *g, t_cmd *cmd, char *redir);
int		ft_heredoc(t_cmd *cmd, char *redir, t_env *lenv);
int		ft_hd_nq(t_cmd *cmd, int *fd, char *del, t_env *lenv);
int		ft_hd_q(t_cmd *cmd, int *fd, char *del);
ssize_t	write_here(const void *buffer, int fd, size_t count);
int		extract_varlen(char *line, int len, char **v_name, bool del_sign);

#endif
