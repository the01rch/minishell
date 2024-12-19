/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:54:36 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/19 12:58:44 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/wait.h>
# define SQUOTE 34
# define DQUOTE 39
# define EALL "Error: allocation failed.\n"
# define FPIPE "bash: syntax error near unexpected token `|'\n"
# define EENV "env: '%s': No such file or directory\n"

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

typedef struct s_command
{
	char	**args;
	char	*redir;
	int		infile;
	int		outfile;
}	t_command;

typedef struct s_global
{
	t_command	**cmds;
	pid_t		pid;
	char		**argv;
	char		**full;
}	t_global;

#endif
