/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:32:16 by kpires            #+#    #+#             */
/*   Updated: 2024/11/25 16:32:16 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

extern int	g_status;

void	*check_args(char *out, t_context *p)
{
    char    **arr;
    int     len;
    t_env	*list;

    (void)p;
	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);

    arr = str2arr(out, " ");
    free(out);
    if (!arr)
            shell_perror(QUOTE, NULL, 1);
    if (!arr)
        return ("");
    len = 0;
    while (p->env[len])
		len++;
	list = arr2list(p->env, len);
    if (gest_builtins(list, arr) == NONE)
			gest_shell(list, arr);
    // while(p.cmds)
    // {
    //     printf("cmds: %s\n", (char *)p.cmds->content);
    //     p.cmds = p.cmds->next;
    // }
    return p;
}
