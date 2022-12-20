/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:29:34 by pgouasmi          #+#    #+#             */
/*   Updated: 2022/12/15 13:11:24 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*temp;

	temp = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buffer) + 1));
	i = 0;
	j = 0;
	while (stash[i])
	{
		temp[i] = stash[i];
		i++;
	}
	free(stash);
	while (buffer[j])
	{
		temp[i + j] = buffer[j];
		j++; 
	}
	temp[i + j] = '\0';
	return (temp);
}

int	find_nl(char *s, int *nl_pres)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			return (1);
			*nl_pres = 1;
		}
	}
return (0);
}

//1 localiser le /n dans le buffer
//2 garder ce qu'il y avant dans stash
//3 envoyer stash dans next line
//4 free stash
char *nl_found(char *buffer, char *stash)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*temp;
	
	i = 0;
	j = 0;
	k = 0;
	while (buffer[i] != '\n')
		i++;
	temp = malloc(sizeof(char) * (i + ft_strlen(stash) + 2));
	while (stash[j])
	{
		temp[j] = stash[j];
		j++;
	}
	while(k <= i)
		temp[j++] = buffer[k++];
	temp[j] = '\0';
	free(stash);
	return (temp);
}

//5 envoyer ce qu'il y a apres le /n dans le stash libere
char	*next_line_ready(char *buffer, char *stash)
{
	size_t	buffer_length;
	size_t	i;
	size_t	j;

	buffer_length = ft_strlen(buffer);
	i = 0;
	while (buffer[i] != '\n')
		i++;
	stash = malloc(sizeof(char) * (buffer_length - i + 1));
	i++;
	j = 0;
	while (buffer[i])
	{
		stash[j] = buffer[i];
		j++;
		i++;
	}
	stash[j] = '\0';
	free(buffer);
	return (stash);
}
