/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:54:36 by redrouic          #+#    #+#             */
/*   Updated: 2024/12/19 09:32:25 by kpires           ###   ########.fr       */
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
	int		infile;
	int		outfile;
	int		prev_fd;
	int		pipe[2];
}	t_command;

typedef struct s_global
{
	t_command	**cmds;
	pid_t		pid;
	char		**argv;
	char		**full;
	int			ext_val;
}	t_global;

#endif
