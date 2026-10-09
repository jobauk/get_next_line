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
#include <unistd.h>

void	fd_getc(int fd, char *out)
{
	static t_state	states[20];
	t_state			*state;

	state = &states[fd];
	if (state->i < (size_t)state->n)
	{
		*out = state->buf[state->i++];
		return ;
	}
	state->i = 0;
	state->n = read(fd, state->buf, sizeof(state->buf));
	if (state->n == -1 || state->n == 0)
		*out = '\0';
	else
		*out = state->buf[state->i++];
}

char	*get_next_line(int fd)
{
	t_string	str;
	char		c;

	str = (t_string){.buf = NULL, .len = 0, .cap = 0};
	while ((fd_getc(fd, &c), c != '\n' && c != '\0'))
		string_push(&str, c);
	if (c == '\n')
		string_push(&str, '\n');
	if (str.buf)
		string_push(&str, '\0');
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
