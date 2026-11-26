/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaukes <jaukes@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/26 01:12:42 by jaukes        #+#    #+#                 */
/*   Updated: 2026/11/26 01:12:45 by jaukes        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdint.h>
#include <stdlib.h>

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

static void	*resize_buffer(void *ptr, size_t used, size_t capacity)
{
	void	*new_ptr;

	new_ptr = malloc(capacity);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, used);
	free(ptr);
	return (new_ptr);
}

static int	string_init(t_string *str, size_t initial)
{
	str->buf = malloc(initial);
	if (!str->buf)
		return (-1);
	str->cap = initial;
	return (0);
}

int	string_push(t_string *str, char c)
{
	if (!str->buf && string_init(str, 128) != 0)
		return (-1);
	if (str->len == str->cap)
	{
		if (str->cap > SIZE_MAX - str->cap / 2)
			return (-1);
		str->cap += str->cap / 2;
		str->buf = resize_buffer(str->buf, str->len, str->cap);
	}
	if (!str->buf)
		return (-1);
	str->buf[str->len++] = c;
	return (0);
}

char	*string_resize_fit(t_string *str)
{
	return (resize_buffer(str->buf, str->len, str->len));
}
