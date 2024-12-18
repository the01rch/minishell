/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:06:06 by kpires            #+#    #+#             */
/*   Updated: 2024/12/18 10:29:51 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../icl/minishell.h"

static  char *ft_file_name(char *line, int i, int j)
{
    char    *file;

    line = line + ft_skip_whitespaces(line);
    i = -1;
    while(line[i++] && !is_in_set(line[i], "<>|"))
    {
        if (line[i] == '\\')
            continue ;
        j++;
    }
    file = malloc(sizeof(char) * (j) + 1 );
    if (!file)
        return (NULL);
    i = -1;
    j = 0;
    while(line[i++] && !is_in_set(line[i], "<>|"))
    {
        if (line[i] == '\\')
            continue ;
        file[j] = line[i];
        j++;
    }
    file[j] = '\0';
    return (file);
}

int	ft_overwrite(t_command *cmd, char *line)
{
	t_command   *cmd2;
    char        *file;

    cmd2 = cmd;
    printf("ft_overwrite\n");
    if (cmd2->outfile > 1)
        close(cmd2->outfile);
    file = ft_file_name(line, 0 , 0);
    if (!file)
        return (-1);
    printf("file:[%s]\n", file);
    cmd->outfile = open(file, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		printf("error ft_overwrite\n");
		free(file);
		return (-1);
	}
    free(file);
    return (1);
}

int ft_append(t_command *cmd, char *line)
{
    t_command   *cmd2;
    char        *file;

    cmd2 = cmd;
    printf("ft_append");
    if (cmd2->outfile > 1)
        close(cmd2->outfile);
    file = ft_file_name(line, 0 , 0);
    if (!file)
        return (-1);
    printf("file:[%s]\n", file);
    cmd->outfile = open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
    if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		printf("error ft_append\n");
		free(file);
		return (-1);
	}
    free(file);
    return (2);
}
