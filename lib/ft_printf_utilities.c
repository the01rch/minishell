/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:46:26 by kpires            #+#    #+#             */
/*   Updated: 2024/12/23 22:46:37 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_ltoa_hexa_size(unsigned long long nb)
{
	int	nlen;

	nlen = 0;
	while (nb > 0)
	{
		nb /= 16;
		nlen++;
	}
	return (nlen);
}

char	*ft_ltoa_hexa(unsigned long long n, char format)
{
	size_t				nlen;
	char				*res;
	unsigned long long	num;

	if (n == 0)
		return (ft_strdup("0"));
	num = n;
	nlen = ft_ltoa_hexa_size(num);
	res = ft_calloc((nlen + 1) * sizeof(char), 1);
	res[nlen--] = '\0';
	while (num > 0)
	{
		res[nlen] = "0123456789abcdef"[(num % 16)];
		if (format == 'X' && (res[nlen] >= 'a' && res[nlen] <= 'f'))
			res[nlen] -= 32;
		num /= 16;
		nlen--;
	}
	return (res);
}

int	ft_utoa_size(long nb)
{
	int	nlen;

	nlen = 0;
	if (nb < 0)
	{
		nlen = 1;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb /= 10;
		nlen++;
	}
	return (nlen);
}

char	*ft_utoa(unsigned int n)
{
	unsigned int	nlen;
	long			num;
	char			*res;

	if (n == 0)
		return (ft_strdup("0"));
	num = n;
	nlen = ft_utoa_size(num);
	res = malloc((nlen + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[nlen--] = '\0';
	while (num > 0)
	{
		res[nlen--] = '0' + (num % 10);
		num /= 10;
	}
	return (res);
}

char	*printf_s(const char *src)
{
	char	*dest;

	if (src == NULL)
		dest = ft_strdup("(null)");
	else
		dest = ft_strdup(src);
	return (dest);
}
