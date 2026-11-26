/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaukes <jaukes@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/12 23:20:17 by jaukes        #+#    #+#                 */
/*   Updated: 2026/11/26 14:30:54 by jaukes        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

static void	*ft_realloc(void *ptr, size_t old, size_t new)
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

static int	string_init(t_string *str, size_t initial)
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

char	*string_resize_fit(t_string *str)
{
	return (ft_realloc(str->buf, str->len, str->len));
}
