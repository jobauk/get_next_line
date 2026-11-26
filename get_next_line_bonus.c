/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaukes <jaukes@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/26 01:11:14 by jaukes        #+#    #+#                 */
/*   Updated: 2026/11/26 01:51:55 by jaukes        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static t_state	**get_state(t_state **node, int fd)
{
	while (*node && (*node)->fd != fd)
		node = &(*node)->next;
	if (!*node)
	{
		*node = malloc(sizeof(**node));
		if (!*node)
			return (node);
		(*node)->fd = fd;
		(*node)->n = 0;
		(*node)->i = 0;
		(*node)->next = NULL;
	}
	return (node);
}

static void	delete_state(t_state **node)
{
	t_state	*state;

	state = *node;
	*node = state->next;
	free(state);
}

static int	fd_getc(t_state *state)
{
	if (state->i >= (size_t)state->n)
	{
		state->i = 0;
		state->n = read(state->fd, state->buf, sizeof(state->buf));
		if (state->n <= 0)
			return ((int)state->n);
	}
	return ((unsigned char)state->buf[state->i++]);
}

static char	*read_line(t_state *state)
{
	t_string	str;
	int			c;

	str = (t_string){0};
	while (1)
	{
		c = fd_getc(state);
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
	if (c < 0 || !str.buf || string_push(&str, '\0') != 0)
	{
		free(str.buf);
		return (NULL);
	}
	return (string_resize_fit(&str));
}

char	*get_next_line(int fd)
{
	static t_state	*states;
	t_state			**node;
	char			*line;
	char			errtest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_state(&states, fd);
	if (!*node)
		return (NULL);
	if ((*node)->i < (size_t)(*node)->n && read(fd, &errtest, 0) < 0)
	{
		delete_state(node);
		return (NULL);
	}
	line = read_line(*node);
	if (!line || (*node)->n <= 0)
		delete_state(node);
	return (line);
}
