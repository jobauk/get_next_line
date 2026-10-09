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
#include <_string.h>
#include <stdio.h>
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

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static char		*ln_end;
	static ssize_t	n;
	t_strbuf		*ln;
	char			*lnbuf;

	ln = NULL;
	ln_end = NULL;
	do {
		if (ln_end)
		{
			ln = strbuf_append(ln, ln_end + 1, (size_t)n - (size_t)(ln_end - buf) - 1);
		}
		n = read(fd, buf, sizeof(buf));
		ln_end = (char *)f_memchr(buf, '\n', (size_t)n);

	} while (n > 0);
	// while (1)
	// {
	// 	ln_end = (char *)f_memchr(buf, '\n', (size_t)n);
	// 	if (ln_end)
	// 	{
	// 		ln = strbuf_append(ln, ln_end + 1, (size_t)n - (size_t)(ln_end - buf) - 1);
	// 		ln = NULL;
	// 	}
	// 	n = read(fd, buf, BUFFER_SIZE);
	// 	if (n <= 0)
	// 	{
	// 		ln = NULL;
	// 		break ;
	// 	}
	// 	ln_end = (char *)f_memchr(buf, '\n', (size_t)n);
	// 	if (ln_end)
	// 	{
	// 		ln = strbuf_append(ln, buf, (size_t)(ln_end - buf));
	// 		break ;
	// 	}
	// 	ln = strbuf_append(ln, buf, (size_t)n);
	// }
	if (n == -1)
	{
		free(ln->buf);
		free(ln);
		return (NULL);
	}
	lnbuf = ln->buf;
	free(ln);
	return (lnbuf);
}

#include <fcntl.h>

int main(void) {
	int fd = open("input.txt", O_RDONLY);

	if (fd == -1)
		return -1;

	puts(get_next_line(fd));
	puts(get_next_line(fd));
	puts(get_next_line(fd));

	return 0;
}
