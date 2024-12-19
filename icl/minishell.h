/* ************************************************************************** */
/*															 */
/*											 :::	 ::::::::   */
/*   minishell.h								:+:	 :+:    :+:   */
/*										  +:+ +:+	    +:+	*/
/*   By: kpires <kpires@student.42.fr>		    +#+  +:+	  +#+	   */
/*									   +#+#+#+#+#+   +#+		 */
/*   Created: 2024/11/06 15:33:18 by redrouic		#+#    #+#		   */
/*   Updated: 2024/12/19 09:33:40 by kpires		 ###   ########.fr	  */
/*															 */
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
# include <fcntl.h>

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
int		count_rows(const char *chr, char *str, bool quote);
void	free_arr(char **arr);
void	listening(void);
void	free_cmds(t_command **cmds);
char	*update_venv(t_env *lenv, char *str);
char	*remq(char *str);
void	free_global(t_global *global);
void	free_node(t_env *node);
int		ft_redir(t_command *cmd, char *line);
bool	ft_str_inc(char *s1, char *s2, size_t n);
int		ft_append(t_command *cmd, char *line);
int		ft_overwrite(t_command *cmd, char *line);
int		is_in_set(char c, char *set);
int		ft_skip_whitespaces(char *str);
int		ft_backslash_count(char *str);
int		ft_redirect_input(t_command *cmd, char *line);
#endif
