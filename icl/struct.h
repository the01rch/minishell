/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:54:36 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/16 12:57:00 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	STRUCT_H 
# define STRUCT_H

# include <sys/wait.h>
# define	SQUOTE	34
# define	DQUOTE	39

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
	char	*exec;
	char	*args;
	char	*full;
	int		infile;
	int		outfile;
	int		fd[2];
}	t_command;

typedef struct s_global
{
	t_command	**cmds;
	pid_t		pid;
	char		**argv;
	char		**full;
}	t_global;

#endif
