/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:54:36 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/24 22:32:00 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/wait.h>
# define SQUOTE 39
# define DQUOTE 34
# define EALL "Error: allocation failed.\n"
# define FPIPE "bash: syntax error near unexpected token `|'\n"
# define EENV "env: '%s': No such file or directory\n"
# define ERR_HD_EOF "warning: here-document delimited by end-of-file\n"
# define ERR_ALLOC "An error has occured, it may\
 be related with a malloc failure\n"

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

typedef struct s_cmd
{
	char	**args;
	char	*redir;
	int		infile;
	int		outfile;
	int		pipe[2];
	int		prev_fd;
}	t_cmd;

typedef struct s_global
{
	t_cmd		*cmds;
	t_env		*list;
	pid_t		last_pid;
	int			exit_val;
}	t_global;

#endif
