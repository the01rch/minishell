/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:33:18 by redrouic          #+#    #+#             */
/*   Updated: 2024/11/18 19:12:09 by redrouic         ###   ########.fr       */
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

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

int		ft_strlen(const char *str);
bool	ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *src);
char	**str2arr(char *str, const char *charset);
void	free_arr(char **arr);
t_env	*arr2list(char **arr, int len);
bool	gest_env(t_env *lenv, char **arr);
bool	gest_builtins(char **arr);
int		arr_len(char **arr);

#endif
