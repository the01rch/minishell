/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:52:04 by kpires            #+#    #+#             */
/*   Updated: 2024/12/22 01:37:30 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../icl/minishell.h"

static int	ft_here_return(t_cmd *cmd, int	*fd, char *line)
{
	close(fd[0]);
	close(fd[1]);
	free(line);
	cmd->infile = -2;
	return (-1);
}

static ssize_t	write_here(const void *buffer, int fd, size_t count)
{
	const char	*buf;
	size_t		total;
	ssize_t		bytes;

	buf = buffer;
	total = 0;
	while (total < count)
	{
		bytes = write(fd, buf + total, count - total);
		if (bytes > 0)
			total += bytes;
		else if (bytes == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				continue ;
			else
				return (-1);
		}
	}
	write(fd, "\n", 1);
	return (total);
}

static int	extract_varlen(char *line, int len, char **v_name)
{
	int	start;
	int	var_len;

	start = len;
	while (line[len] && (ft_isalnum(line[len]) || line[len] == '_'))
		len++;
	var_len = len - start;
	*v_name = malloc(sizeof(char) * (var_len + 1));
	if (!*v_name)
		return (-1);
	ft_strncpy(*v_name, line + start, var_len);
	(*v_name)[var_len] = '\0';
	return (len);
}

char	*init_hd(char *line, t_env *lenv, int i, int v_size)
{
	char	*v_name;
	char	*v_content;
	int		v_len;

	while (line[i])
	{
		if (line[i++] == '$')
		{
			v_len = extract_varlen(line, i, &v_name) - i;
			if (v_len == -1)
				return (NULL);
			v_content = plist(lenv, v_name);
			if (v_content)
			{
				v_size += ft_strlen(v_content);
				free(v_name);
				free(v_content);
			}
			i = v_len + i;
		}
		else
			v_size++;
	}
	return (ft_calloc(v_size + 1, sizeof(char)));
}

char	*fill_hd(char *line, t_env *lenv, char *hd, int i)
{
	char	*v_name;
	char	*v_content;
	int		v_size;

	v_size = 0;
	while (line[i])
	{
		if (line[i++] == '$')
		{
			if (extract_varlen(line, i, &v_name) == -1)
				return (NULL);
			v_content = plist(lenv, v_name);
			if (!v_content)
			{
				free(hd);
				free(v_name);
				return (NULL);
			}
			ft_strlcat(hd + v_size, v_content, ft_strlen(v_content) + 1);
			v_size += ft_strlen(v_content);
			i += extract_varlen(line, i, &v_name);
		}
		else
			hd[v_size++] = line[i - 1];
	}
	hd[v_size] = 0;
	printf("hd:[%s]\n", hd);
	return (hd);
}

char	*ft_here_parse(char *line, t_env *lenv)
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

int	ft_here_nquote(t_cmd *cmd, int *fd, char *del, t_env *lenv)
{
	char	*hd;
	char	*new;

	while (777)
	{
		hd = readline("heredoc> ");
		if (!hd)
		{
			printf("%s\n", ERR_HD_EOF);
			break ;
		}
		if (ft_strncmp(hd, del, ft_strlen(hd))
			&& hd[ft_strlen(del)] == 0)
			break ;
		new = ft_here_parse(hd, lenv);
		if (!new)
			return (ft_here_return(cmd, fd, hd));
		write_here(new, fd[1], ft_strlen(new));
		(free(hd), free(new));
	}
	free(del);
	free(hd);
	close(fd[1]);
	cmd->infile = fd[0];
	return (2);
}
