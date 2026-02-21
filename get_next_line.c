/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozay <mozay@student.42kocaeli.com.tr>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-15 13:20:42 by mozay             #+#    #+#             */
/*   Updated: 2026-02-15 13:20:42 by mozay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*ft_separate_line(char *stash)
{
	int		i;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (stash[++i] && stash[i] != '\n')
		line[i] = stash[i];
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_read(int fd, char *stash)
{
	char	*buffer;
	char	*tmp;
	int		result;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	result = 1;
	while (!ft_strchr(stash, '\n') && result > 0)
	{
		result = read(fd, buffer, BUFFER_SIZE);
		if (result <= 0)
			break ;
		buffer[result] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = tmp;
	}
	free(buffer);
	if (result < 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

static char	*ft_update_stash(char *stash)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new = malloc(ft_strlen(stash + i + 1) + 1);
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		new[j++] = stash[i++];
	new[j] = '\0';
	free(stash);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_separate_line(stash);
	stash = ft_update_stash(stash);
	return (line);
}
