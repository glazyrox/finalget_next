/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgwayne- <rgwayne-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:32:26 by rgwayne-          #+#    #+#             */
/*   Updated: 2019/06/30 23:30:57 by rgwayne-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				ft_find(char *gnl)
{
	int			i;

	i = 0;
	while (gnl[i])
	{
		if (gnl[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int				ft_endit(char *ends)
{
	int			g;

	g = 0;
	while (ends[g])
	{
		if (ends[g] == '\0')
			return (g);
		g++;
	}
	return (g);
}

int				cycle(char **src, char **line)
{
	if (ft_find(*src) >= 0)
	{
		*line = ft_strsub(*src, 0, ft_find(*src));
		*src = ft_fstrsub(*src, ft_find(*src) + 1, ft_strlen(*src), 1);
		return (1);
	}
	if (ft_endit(*src))
	{
		*line = ft_strsub(*src, 0, ft_endit(*src));
		ft_strdel(src);
		return (1);
	}
	else if (src[0] == '\0')
		return (0);
	return (0);
}

int				ft_return(int cnt, char *src)
{
	if (cnt == 0 && !src)
	{
		free(src);
		return (0);
	}
	if (cnt == -1)
		return (-1);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char		arr[BUFF_SIZE + 1];
	static char	*src;
	int			cnt;

	if (fd < 0 || line == NULL)
		return (-1);
	ft_bzero(arr, BUFF_SIZE + 1);
	while ((cnt = read(fd, arr, BUFF_SIZE)) > 0)
	{
		if (src)
			src = ft_fstrjoin(src, arr, 1);
		else
			src = ft_strdup(arr);
		if (ft_find(src) >= 0)
		{
			*line = ft_strsub(src, 0, ft_find(src));
			src = ft_fstrsub(src, ft_find(src) + 1, ft_strlen(src), 1);
			return (1);
		}
		ft_bzero(arr, BUFF_SIZE + 1);
	}
	while ((cnt = read(fd, arr, BUFF_SIZE)) == 0 && src)
		return (cycle(&src, line));
	return (ft_return(cnt, src));
}
