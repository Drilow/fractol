/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:49:33 by adleau            #+#    #+#             */
/*   Updated: 2017/12/22 02:03:44 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <limits.h>
#define X '\n'
#define TMP tmp[fd]

static char		*ft_strchr1(const char *s, int c)
{
	char		*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	str++;
	return (str);
}

static void		gnl_annex(char **tmp, int fd, char *str, char *line_return)
{
	str = TMP;
	TMP = ft_strdup(line_return);
	free(str);
}

int				get_next_line(const int fd, char **line)
{
	int			rd;
	static char	*tmp[OPEN_MAX];
	char		buf[BUFF_SIZE + 1];
	char		*str;
	char		*line_return;

	if (fd < 0 || line == NULL || fd >= OPEN_MAX || (*line = NULL))
		return (-1);
	while ((!TMP || !ft_strchr1(TMP, X)) && (rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = '\0';
		str = TMP;
		TMP = ft_strjoin(TMP, buf);
		ft_strdel(&str);
	}
	if (!TMP || !ft_strlen(TMP))
		return (rd == -1 ? -1 : 0);
	if ((line_return = ft_strchr1(TMP, X)))
	{
		*line = ft_strsub(TMP, 0, line_return - TMP - 1);
		gnl_annex(tmp, fd, str, line_return);
	}
	else if (!line_return && (*line = ft_strdup(TMP)) != NULL)
		ft_strdel(&TMP);
	return (1);
}
