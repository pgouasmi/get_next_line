/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:21:18 by pgouasmi          #+#    #+#             */
/*   Updated: 2022/12/16 16:04:00 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_nl(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *buffer, char *stash)
{
	size_t	i;
	size_t	j;
	char	*result;
	size_t	total_length;

	i = 0;
	j = 0;
	if (!stash)
	{
		stash = malloc(sizeof(char) * 1);
		stash[0] = '\0';
	}
	if (!stash || !buffer)
		return (NULL);
	total_length = ft_strlen(stash) + ft_strlen(buffer);
	result = malloc(sizeof(char) * (total_length + 1));
	if (!result)
		return (NULL);
	while (stash[i])
	{
		result[i] = stash[i];
		i++;
	}
	while (buffer[j])
	{
		result[i + j] = buffer[j];
		j++;
	}
	result[total_length] = '\0';
	free (stash);
	return (result);
}

char	*send_to_line(char *stash)
{
	size_t	i;
	char	*s;

	if (!stash)
		return(NULL);
	i = 0;
	while(stash[i] != '\n' && stash[i])
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	i = 0;
	while(stash[i] != '\n' && stash[i])
	{
		s[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		s[i] = stash[i]; 
		i++;
	}
	s[i] = '\0';
	return (s);
}


char	*stash_ready(char *stash)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while(stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	temp = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!temp)
		return (NULL);
	i++;
	while(stash[i])
	{
		temp[j] = stash[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	free(stash);
	return (temp);
}

char	*read_save(int fd, char *stash)
{
	int		char_count;
	char	*buffer;

	char_count = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return(NULL);
	while (char_count != 0 && !check_nl(stash))
	{
		char_count = read(fd, buffer, BUFFER_SIZE);
		if (char_count == -1)
		{
			free(buffer);
			return(NULL);
		}
		buffer[char_count] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free (buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || read(fd, &line, BUFFER_SIZE) == -1)
		return (NULL);
// check si fichier bien appele et si read fonctionne
	stash = read_save(fd, stash); // envoie buffer dans stash en join
	if(!stash)
		return(NULL);
	line = send_to_line(stash);
	stash = stash_ready(stash);
	return (line);
}