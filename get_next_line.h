/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaukes <jaukes@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/09/29 14:41:24 by jaukes        #+#    #+#                 */
/*   Updated: 2026/09/29 14:47:45 by jaukes        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdio.h>

# define BUFFER_SIZE 1

typedef struct s_strbuf
{
	size_t	len;
	char	*buf;
}			t_strbuf;

typedef struct s_state
{
	char	buf[BUFFER_SIZE];
	ssize_t	size;
	size_t	remaining;
}			t_state;

char	*get_next_line(int fd);

void	*f_memchr(const void *s, int c, size_t n);

#endif
