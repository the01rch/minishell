/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:51:12 by kpires            #+#    #+#             */
/*   Updated: 2024/11/29 14:51:12 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

static  int ft_cw_quotes(char *str, char *del, int cnt[2])
{
    int qt[2];

    qt[0] = 0;
    qt[1] = 1;
    while (str[cnt[0]] != '\0')
    {
        if (!ft_strchr(del, str[cnt[0]]))
        {
            cnt[1]++;
            while ((!ft_strchr(del, str[cnt[0]]) || qt[0]) && str[cnt[0]])
            {
                if (!qt[1] && (str[cnt[0]] == '\"' || str[cnt[0]] == '\''))
                    qt[1] = str[cnt[0]];
                qt[0] = (qt[0] + (str[cnt[0]] == '\"' || str[cnt[0] == '\''])) % 2;
                qt[1] *= qt[0];
                cnt[0]++;
            }
            if (qt[1])
                return -1;
        }
        else
            cnt[0]++;
    }
    return (cnt[1]);
}

static char    **fill(char **filled, char *str, char *del, int i[3])
{
    int s_len;
    int qt[2];
    int start;

    qt[0] = 0;
    qt[1] = 0;
    s_len = strlen(str);
    start = 0;
    (void)qt;
    (void)s_len;
    while (str[i[0]])
    {
        if (strchr(del, str[i[0]]) != NULL)
        {
            filled[i[1]] = strndup(&str[start], i[0] - start);
            i[1]++;
            start = i[0] + 1;
        }
        i[0]++;
    }
    filled[i[1]] = strndup(&str[start], i[0] - start);
    filled[i[1] + 1] = NULL;

    return filled;
}

char    **ft_split_quotes(const char *str, char *del)
{
    char    **str_split;
    int     words;
    int     count[2];
    int     i[3];

    if (!str)
        return (NULL);
    str_split = NULL;
    count[0] = 0;
    count[1] = 0;
    words = ft_cw_quotes((char *)str, del, count);
    if (words == -1)
        return (NULL);
    str_split = malloc(sizeof(char *) * (words + 1));
    if (!str_split)
        return (NULL);
    i[0]= 0;
    i[1] = 0;
    i[2] = 0;
    str_split = fill(str_split, (char *)str, del, i);
    printf("test ft cw quotes %d\n", words);
    return (str_split);
}