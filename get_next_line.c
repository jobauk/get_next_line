/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaukes <jaukes@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/09/29 14:41:24 by jaukes        #+#    #+#                 */
/*   Updated: 2026/09/29 14:47:45 by jaukes        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int	fd_getc(int fd)
{
	static t_state	states[20];
	t_state			*state;

	state = &states[fd];
	if (state->n <= 0 || state->i >= (size_t)state->n)
	{
		state->i = 0;
		state->n = read(fd, state->buf, sizeof(state->buf));
		if (state->n <= 0)
			return ((int)state->n);
	}
	return (state->buf[state->i++]);
}

char	*get_next_line(int fd)
{
	t_string	str;
	int			c;

	str = (t_string){0};
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
	if (c == -1 || (str.buf && string_push(&str, '\0') != 0))
	{
		free(str.buf);
		return (NULL);
	}
	return (str.buf);
}

// #include <fcntl.h>
// #include "stdio.h"

// int main(void) {
// 	int fd = open("small.txt", O_RDONLY);
// 	if (fd == -1)
// 		return -1;

// 	printf("\"%s\"\n", get_next_line(fd));
// 	printf("\"%s\"\n", get_next_line(fd));

// 	// close(fd);
// 	fd = open("input.txt", O_RDONLY);
// 	if (fd == -1)
// 		return -1;

// 	printf("\"%s\"\n", get_next_line(fd));
// 	printf("\"%s\"\n", get_next_line(fd));

// 	return 0;
// }
