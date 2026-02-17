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

char	*ft_trim(char *str)
{
	char	*newstr;

	newstr = (char *) malloc (sizeof(char));
	if (!str)
		return (NULL);
	while (*str != '\n')
		*(newstr)++ = *(str)++;
	*newstr = '\0';
	return (newstr);
}

char	*ft_read(int fd, char *str)
{
	char	*newstr;
	int		result;

	result = 0;
	newstr = (char *) malloc (BUFFER_SIZE + 1);
	if (!newstr)
		return (NULL);
	while (!ft_strchr(str, '\n') && str)
	{	
		result = read(fd, newstr, BUFFER_SIZE);
		if (result == 0)
			break ;
		else if (result == -1)
		{
			free(newstr);
			free(str);
			str = NULL;
			return (NULL);
		}
		else if (result)
			newstr[result] = '\0';
		newstr = ft_strjoin(str, newstr);
	}
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if ((fd < 0) || (BUFFER_SIZE < 0) || (read(fd, NULL, 0) < 0))
		return (NULL);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	line = ft_trim(str);
	return (line);
}
