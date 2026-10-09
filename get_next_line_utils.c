/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
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
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	return (memcpy(dst, src, n));
}

void	*ft_realloc(void *ptr, size_t old, size_t new)
{
	void	*new_ptr;

	new_ptr = malloc(new);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, old);
	free(ptr);
	return (new_ptr);
}

int	string_init(t_string *str, size_t initial)
{
	str->buf = malloc(initial * sizeof(char));
	if (!str->buf)
		return (-1);
	str->cap = initial;
	return (0);
}

int	string_push(t_string *str, char c)
{
	if (!str->buf && string_init(str, 128) != 0)
		return (-1);
	if (str->len + 1 >= str->cap)
	{
		str->cap = (size_t)((double)str->cap * 1.5);
		str->buf = ft_realloc(str->buf, str->len, str->cap);
	}
	if (!str->buf)
		return (-1);
	str->buf[str->len++] = c;
	return (0);
}
