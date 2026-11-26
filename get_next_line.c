/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaukes <jaukes@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/09/29 14:41:24 by jaukes        #+#    #+#                 */
/*   Updated: 2026/11/26 01:07:26 by jaukes        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int	fd_getc(int fd)
{
	static t_state	states[NSTATES];
	t_state			*state;

	if (fd >= NSTATES || fd == -1)
		return (-1);
	state = &states[fd];
	if (state->n <= 0 || state->i >= (size_t)state->n)
	{
		state->i = 0;
		state->n = read(fd, state->buf, sizeof(state->buf));
		if (state->n <= 0)
			return ((int)state->n);
	}
	return ((unsigned char)state->buf[state->i++]);
}

char	*get_next_line(int fd)
{
	t_string	str;
	int			c;

	str = (t_string){0};
	if (fd == -1)
		return (NULL);
	while (1)
	{
		c = fd_getc(fd);
		if (c <= 0)
			break ;
		if (string_push(&str, (char)c) != 0)
		{
			free(str.buf);
			return (NULL);
		}
		if (c == '\n')
			break ;
	}
	if (c == -1 || (str.buf && string_push(&str, '\0') != 0) || !str.buf)
	{
		free(str.buf);
		return (NULL);
	}
	return (string_resize_fit(&str));
}

#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	int fd;

	fd = open("input.txt", O_CREAT | O_RDWR);
	// write(fd, "0", 1);
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));

	// close(fd);
	// fd = open("input.txt", O_RDONLY);
	// printf("\"%s\"\n", get_next_line(fd));
	// printf("\"%s\"\n", get_next_line(fd));

	// fd = open("files/empty", O_RDWR);
	// printf("\"%s\"\n", get_next_line(fd));
	// printf("\"%s\"\n", get_next_line(fd));

	return 0;
}
