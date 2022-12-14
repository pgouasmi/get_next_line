/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:29:38 by pgouasmi          #+#    #+#             */
/*   Updated: 2022/12/14 16:47:36 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

void	read_save(int fd, char *stash, char *next_line)
{
	char	*buffer;
	size_t	char_count;
	int		nl_pres;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	char_count = 1;
	if (!buffer)
		return;
	//tant qu'il n y a pas de \n dans buffer
	while (!find_nl(buffer, &nl_pres) && char_count > 0)
	{
		char_count = read(fd, buffer, BUFFER_SIZE); // on continue a lire
		if (char_count <= 0)
		{
			next_line = NULL;
			return;
		}
		stash = ft_strjoin(stash, buffer);// on ajoute buffer a stash
		if (!stash)
			return;
	}
	if (nl_pres == 1)
	{
		next_line = nl_found(buffer, stash);
		stash = next_line_ready(buffer, stash);
	}
	else
		next_line = NULL;
	return;
	//1 localiser le /n dans le buffer
	//2 garder ce qu'il y avant dans stash
	//3 envoyer stash dans next line
	//4 free stash
	//5 envoyer ce qu'il y a apres le /n dans le stash libere
}

char	*get_next_line(int fd)
{
	char	*next_line;
	char	*stash;

	stash = NULL;
// check si fichier bien appele et si read fonctionne
	if (fd < 0 || read(fd, &next_line, BUFFER_SIZE) < 0)
		return (NULL);
// appelle fonction qui va read, et copier le buffer dans stash 
// tant qu'il n'y a pas de \n
	read_save(fd, stash, next_line);
	if (!stash)
		next_line = NULL;
	stash = next_line_ready(buffer, stash);
	return (next_line);
}
 