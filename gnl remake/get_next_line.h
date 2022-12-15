/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:29:42 by pgouasmi          #+#    #+#             */
/*   Updated: 2022/12/15 15:21:03 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE = 10

char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *stash, char *buffer);
int		find_nl(char *s, int *nl_pres);
char	*nl_found(char *buffer, char *stash);
char	*next_line_ready(char *buffer, char *stash);

#endif