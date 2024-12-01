#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
    int	count;

    count = 0;
    if (!s)
        return (count);
    while (*s != '\0')
    {
        count++;
        s++;
    }
    return (count);
}

char	*ft_strchr(const char *s, int c)
{
    unsigned char	c_unsigned;

    c_unsigned = (unsigned char)c;
    if (c_unsigned == '\0')
        return ((char *)&s[ft_strlen(s)]);
    while (*s != '\0')
    {
        if (*s == c_unsigned)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

static int	ft_count_words(const char *s, char *c, int i[2])
{
    int		q[2];

    q[0] = 0;
    q[1] = 0;
    while (s[i[0]] != '\0')
    {
        if (!ft_strchr(c, s[i[0]]))
        {
            i[1]++;
            while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
            {
                if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
                    q[1] = s[i[0]];
                q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
                q[1] *= q[0] != 0;
                i[0]++;
            }
            if (q[0])
                return (-1);
        }
        else
            i[0]++;
    }
    return (i[1]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			size_src;

	i = 0;
	if (src == NULL)
		return (0);
	size_src = ft_strlen(src);
	if ((int)size < 0)
		size = size_src + 1;
	if (size >= 2 && size_src != 0)
	{
		while (i < size - 1)
		{
			if (i < size_src)
				dst[i] = src[i];
			else if (i == size_src)
				dst[i] = '\0';
			i++;
		}
	}
	if (size != 0)
		dst[i] = '\0';
	return (size_src);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	if (len > s_len)
		len = s_len;
	if (start >= s_len)
	{
		substr = (char *)malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr = (char *)malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	while (i++ < start)
		s++;
	ft_strlcpy(substr, s, len + 1);
	return (substr);
}


int count_word(const char *str, char *del, int cnt[2])
{
    int qt[2];

    qt[0] = 0;
    qt[1] = 0;
    while (str[cnt[0]] != '\0')
    {
        if (!ft_strchr(del, str[cnt[0]]))
        {
            cnt[1]++;
            while ((!ft_strchr(del, str[cnt[0]]) || qt[0]) && str[cnt[0]] != '\0')
            {
                if (!qt[1] && (str[cnt[0]] == '\"' || str[cnt[0]] == '\''))
                    qt[1] = str[cnt[0]];
                qt[0] = (qt[0] + (str[cnt[0]] == qt[1])) % 2;
                qt[1] *= qt[0];
                cnt[0]++;
            }
            if (qt[0])
                return -1;
        }
        else
            cnt[0]++;
    }
    return cnt[1];
}

char    **fill_array(char **cut, char const *str, const char *del, int i[3])
{
    int str_len;
    int qt[2];

    qt[0] = 0;
    qt[1] = 0;
    str_len = ft_strlen(str);
    while (str[i[0]])
    {
        while (ft_strchr(del, str[i[0]]) && str[i[0]] != '\0')
            i[0]++;
        i[1] = i[0];
        while (!ft_strchr(del, str[i[0]] || qt[0] || qt[1]) && str[i[0]])
        {
            qt[0] = (qt[0] + (!qt[1] && str[i[0]] == '\'')) % 2;
            qt[1] = (qt[1] + (!qt[0] && str[i[0]] == '\"')) % 2;
            i[0]++;
        }
        if (i[1] > str_len)
            cut[i[2]++] = "\0";
        else
            cut[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
    }
    return cut;
}

char    **ft_cmdtrim(const char *str, char *del)
{
    int counts[2];
    char    **cut;
    int i[3];

    counts[0] = 0;
    counts[1] = 0;
    i[0] = 0;
    i[1] = 1;
    i[2] = 0;
    int words = count_word(str, del, counts);
    if (words == -1)
        return NULL;
    printf("[%s] count word:[%d]\n", str, words);
    cut = malloc(sizeof(char *) * (words + 1));
    if(!cut)
        return NULL;
    cut = fill_array(cut, str, del, i);
    cut[words] = NULL;
    return cut;
}

void print_result(char **result) {
    int i = 0;
    while (result[i]) {
        printf("\"%s\"\n", result[i]);
        i++;
    }
}


int main() {
    char *test_cases[] = {
        "echo 'It\\'s a \"beautiful\" day'",
        "echo 'Hello, world!' 'How are you?'",
        "echo 'This is a \"test\"' 'Another test'",
        "echo \"Hello\" 'world'",
        "echo 'single' \"double\" 'mixed \"quotes\"'",
        "echo   'my   \"complex\"   string'",
        "echo 'escaped \\'single\\' quotes'",
        NULL
    };
    char *delimiters = " ";

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("Test case %d: \"%s\"\n", i + 1, test_cases[i]);

        char **result_ft_cmdtrim = ft_cmdtrim(test_cases[i], delimiters);
        printf("ft_cmdtrim result:\n");
        print_result(result_ft_cmdtrim);

        printf("\n");

        // Libérer la mémoire allouée
        for (int j = 0; result_ft_cmdtrim[j] != NULL; j++) {
            free(result_ft_cmdtrim[j]);
        }
        free(result_ft_cmdtrim);
    }

    return 0;
}