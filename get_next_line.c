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

static char	*ft_seperate_line(char *stash)
{
	char	*newstr;
	int		i;
	int		j;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	newstr = (char *) malloc (i + 1);
	if (!newstr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		newstr[j] = stash[j];
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}

static char	*ft_read(int fd, char *stash)
{
	char	*buffer;
	int		result;
	char	*temp;

	if (!stash)
	{
		stash = (char *) malloc (1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	buffer = (char *) malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	result = 1;
	while (!ft_strchr(stash, '\n') && result > 0)
	{
		result = read(fd, buffer, BUFFER_SIZE);
		if (result == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (result > 0)
		{
			buffer[result] = '\0';
			temp = ft_strjoin(stash, buffer);
			if (!temp)
			{
				free(buffer);
				return (stash);
			}
			free(stash);
			stash = temp;
		}
	}
	free(buffer);
	return (stash);
}

static char	*ft_update_stash(char *stash)
{
	int		i;
	int		j;
	char	*newstash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	i++;
	newstash = (char *) malloc (ft_strlen(stash + i) + 1);
	if (!newstash)
		return (NULL);
	j = 0;
	while (stash[i + j] != '\0')
	{
		newstash[j] = stash[i + j];
		j++;
	}
	newstash[j] = '\0';
	free(stash);
	return (newstash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_seperate_line(stash);
	stash = ft_update_stash(stash);
	return (line);
}

#include <stdio.h>
#include <fcntl.h>
int main(){
	int fd = open("dosya.txt", O_RDONLY);
	char *line1 = get_next_line(fd);
	char *line2 = get_next_line(fd);
	char *line3 = get_next_line(fd);
	
	printf("%s\n", line1);
	printf("%s\n", line2);
	printf("%s\n", line3);
	
	free(line1);
	free(line2);
	free(line3);
	close(fd);
	return (0);
}