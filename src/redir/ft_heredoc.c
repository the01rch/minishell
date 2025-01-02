/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:52:04 by kpires            #+#    #+#             */
/*   Updated: 2025/01/02 22:47:39 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*init_hd(char *line, t_env *lenv, int i, size_t total_size)
{
	char	*v_name;
	char	*v_content;

	while (i < ft_strlen(line) && line[i])
	{
		if (line[i] == '$')
		{
			i = extract_varlen(line, ++i, &v_name, true);
			if (i == -1)
				return (NULL);
			v_content = plist(lenv, v_name);
			free(v_name);
			if (v_content)
			{
				total_size += ft_strlen(v_content);
				free(v_content);
			}
			else
				total_size++;
		}
		else
			total_size++;
		i++;
	}
	return (ft_calloc(total_size + 1, sizeof(char)));
}

static char	*fill_hd(char *line, t_env *lenv, char *hd, int i)
{
	char	*v_name;
	char	*v_content;
	int		v_size;

	v_size = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i = extract_varlen(line, ++i, &v_name, false);
			if (i == -1)
				return (NULL);
			v_content = plist(lenv, v_name);
			free(v_name);
			if (!v_content)
				continue ;
			ft_strlcat(hd + v_size, v_content, ft_strlen(v_content) + 1);
			v_size += ft_strlen(v_content);
			free(v_content);
		}
		else
			hd[v_size++] = line[i++];
	}
	hd[v_size] = 0;
	return (hd);
}

static char	*ft_here_parse(char *line, t_env *lenv)
{
	char	*hd;

	hd = init_hd(line, lenv, 0, 0);
	if (!hd)
		return (printf("%s\n", ERR_ALLOC), NULL);
	hd = fill_hd(line, lenv, hd, 0);
	if (!hd)
		return (NULL);
	return (hd);
}

int	ft_hd_q(t_cmd *cmd, int *fd, char *del)
{
	char	*hd;

	while (777)
	{
		hd = readline("heredoc (not parsed)> ");
		if (!hd)
		{
			printf("%s\n", ERR_HD_EOF);
			break ;
		}
		if ((ft_strncmp(hd, del, ft_strlen(del)) == 0
				&& hd[ft_strlen(del)] == 0))
			break ;
		write_here(hd, fd[1], ft_strlen(hd));
		free(hd);
	}
	(free(del), free(hd), close(fd[1]));
	cmd->infile = fd[0];
	return (2);
}

int	ft_hd_nq(t_cmd *cmd, int *fd, char *del, t_env *lenv)
{
	char	*hd;

	while (777)
	{
		hd = readline("heredoc> ");
		if (!hd)
		{
			printf("%s\n", ERR_HD_EOF);
			break ;
		}
		if ((ft_strncmp(hd, del, ft_strlen(del)) == 0
				&& hd[ft_strlen(del)] == 0))
			break ;
		hd = ft_here_parse(hd, lenv);
		if (!hd)
		{
			cmd->infile = -2;
			return (close(fd[0]), close(fd[1]), free(del), (int)-1);
		}
		write_here(hd, fd[1], ft_strlen(hd));
		(free(hd));
	}
	(free(del), free(hd), close(fd[1]));
	cmd->infile = fd[0];
	return (2);
}
