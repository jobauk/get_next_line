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

# define BUFFER_SIZE 1024

# define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct s_strbuf {
	size_t	len;
	// size_t	cap;
	char	*buf;
}			t_strbuf;

char	*get_next_line(int fd);

void	*f_memchr(const void *s, int c, size_t n);

#endif
