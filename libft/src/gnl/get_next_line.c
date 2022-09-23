/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:20:04 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/16 16:53:31 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *str)
{
	size_t	n;
	char	*ptr;

	if (!*str)
		return (NULL);
	n = 0;
	while (str[n] && str[n] != '\n')
		n++;
	ptr = ft_calloc(n + 2, sizeof(char));
	if (!ptr)
		return (NULL);
	n = 0;
	while (str[n] && str[n] != '\n')
	{
		ptr[n] = str[n];
		n++;
	}
	if (str[n] == '\n')
	{
		ptr[n] = str[n];
		n++;
	}
	return (ptr);
}

static char	*keep_remains(char *str)
{
	size_t	n;
	size_t	j;
	char	*ptr;

	n = 0;
	while (str[n] && str[n] != '\n')
		n++;
	if (!str[n])
	{
		free (str);
		return (NULL);
	}
	n++;
	ptr = ft_calloc(ft_strlen(&str[n]) + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	j = 0;
	while (str[n] && str[n])
		ptr[j++] = str[n++];
	ptr[j] = '\0';
	free(str);
	return (ptr);
}

static char	*read_file(int fd, char *str)
{
	char	*buf;
	int		is_end;

	is_end = 1;
	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (NULL);
	write(1, "> ", 2);
	while (!ft_strchr(buf, '\n') && is_end != 0)
	{
		is_end = read(fd, buf, BUFFER_SIZE);
		if (is_end == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[is_end] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_file(fd, str);
	if (!str)
		return (NULL);
	line = get_line(str);
	str = keep_remains(str);
	return (line);
}
