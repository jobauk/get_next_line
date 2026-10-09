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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

static t_strbuf	*strbuf_init(const char *src, size_t len)
{
	t_strbuf	*strbuf;

	strbuf = malloc(sizeof(t_strbuf));
	if (!strbuf)
		return (NULL);
	strbuf->buf = malloc((len + 1) * sizeof(char));
	if (!strbuf->buf)
	{
		free(strbuf);
		return (NULL);
	}
	memcpy(strbuf->buf, src, len);
	strbuf->buf[len] = '\0';
	strbuf->len = len;
	return (strbuf);
}

static t_strbuf	*strbuf_append(t_strbuf *strbuf, const char *src, size_t len)
{
	if (!strbuf)
		return (strbuf_init(src, len));
	strbuf->buf = realloc(strbuf->buf, (strbuf->len + len + 1) * sizeof(char));
	if (!strbuf->buf)
	{
		free(strbuf);
		return (NULL);
	}
	memcpy(strbuf->buf + strbuf->len, src, len);
	strbuf->len += len;
	strbuf->buf[strbuf->len] = '\0';
	return (strbuf);
}
// 0 + 5 - 3 = 2
// start: 2
// delim: 4
static t_strbuf	*strbuf_append_until(t_strbuf *strbuf, t_state *state)
{
	char	*start;
	char	*delim;

	start = state->buf + state->size - state->remaining;
	delim = f_memchr(start, '\n', state->remaining);
	if (!delim)
	{
		strbuf = strbuf_append(strbuf, start, state->remaining);
		state->remaining = 0;
	}
	else
	{
		strbuf = strbuf_append(strbuf, start, (size_t)(delim - start + 1));
		state->remaining -= (size_t)(delim - start + 1);
	}
	return (strbuf);
}

char	*get_next_line(int fd)
{
	static t_state	state;
	t_strbuf		*strbuf;

	strbuf = NULL;
	while (1)
	{
		strbuf = strbuf_append_until(strbuf, &state);
		if (!strbuf || state.remaining)
			break ;
		if (state.size > 0 && state.buf[state.size - 1] == '\n')
		{
			state.size = 0;
			break ;
		}
		if (!state.remaining && !(state.size > 0 && state.buf[state.size - 1] == '\n'))
		{
			state.size = read(fd, state.buf, sizeof(state.buf));
			if (state.size > 0)
				state.remaining = (size_t)state.size;
		}
		if (state.size <= 0)
			break ;
	}
	if (state.size == -1 || strbuf->len == 0)
		return (NULL);
	return (strbuf->buf);
}

#include <fcntl.h>

int main(void) {
	int fd = open("input.txt", O_RDONLY);

	if (fd == -1)
		return -1;

	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));
	printf("\"%s\"\n", get_next_line(fd));

	return 0;
}
