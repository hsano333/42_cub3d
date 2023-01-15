/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 03:21:52 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/15 19:50:50 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **p)
{
	if (p)
	{
		free(*p);
		*p = NULL;
	}
}

char	*ft_file_read_helper(int fd, char *store, \
	char buf[BUFFER_SIZE], int *len)
{
	char	*tmp;
	int		size;

	size = ft_strlen(store);
	while (*len > 0)
	{
		tmp = malloc((size + *len + 1) * sizeof(char));
		if (!(tmp))
		{
			ft_free(&store);
			break ;
		}
		tmp = ft_memcpy(tmp, store, size);
		free(store);
		ft_memcpy(tmp + size, buf, *len);
		store = tmp;
		size += *len;
		store[size] = '\0';
		if (ft_strchr(store, '\n'))
			break ;
		*len = read(fd, buf, BUFFER_SIZE);
	}
	return (store);
}

char	*ft_file_read(int fd, char *store)
{
	char	buf[BUFFER_SIZE];
	int		len;

	if (!store)
	{
		store = (char *)malloc(sizeof(char));
		if (!(store))
			return (NULL);
		*store = '\0';
	}
	if (ft_strchr(store, '\n'))
		return (store);
	len = read(fd, buf, BUFFER_SIZE);
	if (ft_strlen(store) == 0 && len == 0)
	{
		ft_free(&store);
		return (NULL);
	}
	else if (store && len == 0)
		return (store);
	store = ft_file_read_helper(fd, store, buf, &len);
	if (len == -1)
		ft_free(&store);
	return (store);
}

int	split_by_n(char *store, char **line, char **newstore, char *location_n)
{
	if (store == NULL)
	{
		ft_free(line);
		return (1);
	}
	if (location_n == NULL)
		return (0);
	*line = ft_substr(store, 0, ft_strlen(store) - ft_strlen(location_n + 1));
	*newstore = ft_strdup(location_n + 1);
	if (*line == NULL || *newstore == NULL)
	{
		ft_free(line);
		ft_free(newstore);
	}
	else if (ft_strlen(*newstore) == 0)
		ft_free(newstore);
	ft_free(&store);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	char		*line;

	line = NULL;
	if (0 > fd || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	store[fd] = ft_file_read(fd, store[fd]);
	if (store[fd])
	{
		if (split_by_n(store[fd], &line, &store[fd], \
					ft_strchr(store[fd], '\n')))
			;
		else
		{
			line = ft_substr(store[fd], 0, ft_strlen(store[fd]));
			ft_free(&store[fd]);
		}
	}
	else
		ft_free(&store[fd]);
	return (line);
}
