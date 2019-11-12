/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgwayne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:39:23 by rgwayne-          #+#    #+#             */
/*   Updated: 2018/12/16 14:33:51 by rgwayne-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_wlen(const char *s, int start, char c)
{
	int		length;

	length = 0;
	while (s[start++] != c)
	{
		length++;
	}
	return (length);
}

static char		**ft_wrds_prc(const char *s, char c, char **res)
{
	int		count;
	char	*temp;
	int		i;
	int		j;

	j = 0;
	i = -1;
	temp = (char*)s;
	count = 0;
	while (temp[i++] == c)
		;
	while (temp[i] != '\0')
	{
		while (temp[i] == c && temp[i] != '\0')
			i++;
		if (temp[i] == '\0')
			return (res);
		if (!(res[j++] = ft_strsub(temp, i, ft_count_wlen(temp, i, c))))
			ft_freearr(res, j);
		while (temp[i] != c && temp[i] != '\0')
			i++;
		count++;
	}
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	int		len;
	char	**res;
	int		i;

	i = 0;
	res = NULL;
	if (s == NULL)
		return (NULL);
	while (s[i] == c)
		i++;
	if (!s[i])
		return (res = ft_memalloc(sizeof(char*)));
	len = ft_count_words(s, c);
	res = (char**)malloc(sizeof(char*) * (len + 1));
	if (res == NULL)
		return (NULL);
	res = ft_wrds_prc(s, c, res);
	res[len] = NULL;
	return (res);
}
