/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:53:50 by kpires            #+#    #+#             */
/*   Updated: 2024/11/25 15:53:50 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

extern int	g_status;

static char	*get_home(t_context prompt)
{
	char	*temp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = shell_getenv("HOME", prompt.env, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(temp);
	}
	free(home);
	home = ft_strjoin(NULL, pwd);
	free(pwd);
	pwd = ft_strjoin(home, " ");
	free(home);
	home = ft_strjoin(" ", pwd);
	free(pwd);
	pwd = ft_strjoin(home, NULL);
	free(home);
	return (pwd);
}

static char	*get_user(t_context prompt)
{
	char	**user;
	char	*temp;

	user = NULL;
	exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.env);
	if (!user)
		user = ft_extend_matrix(user, "guest");
	temp = ft_strjoin(NULL, *user);
	ft_free_matrix(&user);
	return (temp);
}

char	*shell_getprompt(t_context prompt)
{
	char	*temp;
	char	*temp2;
    char    *aux;

	temp = get_user(prompt);
	temp2 = ft_strjoin(temp, "@minishell:");
    free(temp);
    aux = get_home(prompt);
    temp = ft_strjoin(temp2, aux);
    free(aux);
    free(temp2);
	if (!g_status || g_status == -1)
		temp2 = ft_strjoin(temp, NULL);
	else
		temp2 = ft_strjoin(temp, NULL);
    free(temp);
    temp = ft_strjoin(temp2, "$> ");
    free(temp2);
    temp2 = ft_strjoin(temp, NULL);
    free(temp);
	return (temp2);
}