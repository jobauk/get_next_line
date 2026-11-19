/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaukes <jaukes@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/12 23:24:07 by jaukes        #+#    #+#                 */
/*   Updated: 2026/10/12 23:24:13 by jaukes        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef NSTATES
#  define NSTATES 100
# endif

typedef struct s_state
{
	char	buf[BUFFER_SIZE];
	size_t	i;
	ssize_t	n;
}			t_state;

typedef struct s_string
{
	char	*buf;
	size_t	len;
	size_t	cap;
}			t_string;

void	*ft_memcpy(void *dst, const void *src, size_t n);

void	*ft_realloc(void *ptr, size_t old, size_t new);

char	*get_next_line(int fd);

int		string_init(t_string *str, size_t initial);

int		string_push(t_string *str, char c);

char	*string_resize_fit(t_string *str);

#endif
