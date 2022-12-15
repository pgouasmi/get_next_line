/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:21:18 by pgouasmi          #+#    #+#             */
/*   Updated: 2022/12/15 17:00:43 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

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

	i = 0;
	j = 0;
	while(stash[i])
		i++;
	while(buffer[j])
	{
		stash[i + j] = buffer[j];
		j++;
	}
	stash[i + j] = '\0';
	return (stash);
}

char	*send_to_line(char *stash, char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while(stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	i = 0;
	while(stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	return (line);
}


char	*stash_ready(char *stash)
{
	size_t	stash_length;
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * SIZE_MAX);
	stash_length = ft_strlen(stash);
	while(stash[i] != '\n')
		i++;
	while(stash[i])
	{
		temp[j] = stash[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	i = 0;
	while(stash[i++])
		stash[i] = '\0';
	i = 0;
	while(temp[i])
	{
		stash[i] = temp[i];
		i++;
	}
	return (stash);
}

void	read_save(int fd, char *stash)
{
	int		char_count;
	char	*buffer;

	char_count = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	while (char_count && !check_nl(stash))
	{
		char_count = read(fd, buffer, BUFFER_SIZE);
		// buffer[BUFFER_SIZE + 1] = '\0';
		stash = ft_strjoin(buffer, stash);
	}
	return;
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || read(fd, &line, BUFFER_SIZE) < 0)
		return (NULL);
	stash = malloc(sizeof(char) * 10000);
	stash[0] = '\0'; 
	line = NULL;
// check si fichier bien appele et si read fonctionne
	read_save(fd, stash); // envoie buffer dans stash en join
	if(stash[0] == '\0')
		return (NULL);
	line = send_to_line(stash, line);
	stash = stash_ready(stash);
	return (line);
}