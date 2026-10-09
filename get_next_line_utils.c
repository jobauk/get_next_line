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

#include <stddef.h>
#include <stdint.h>

static inline uint64_t	read_u64(const void *s)
{
	const unsigned char	*p;
	uint64_t			word;

	p = s;
	word = (uint64_t)p[0];
	word |= (uint64_t)p[1] << 8;
	word |= (uint64_t)p[2] << 16;
	word |= (uint64_t)p[3] << 24;
	word |= (uint64_t)p[4] << 32;
	word |= (uint64_t)p[5] << 40;
	word |= (uint64_t)p[6] << 48;
	word |= (uint64_t)p[7] << 56;
	return (word);
}

static inline size_t	indexof_non_zero_byte(uint64_t word)
{
	size_t	i;

	i = 0;
	if (!(word & 0xffffffffULL))
	{
		word >>= 32;
		i += 4;
	}
	if (!(word & 0xffffULL))
	{
		word >>= 16;
		i += 2;
	}
	if (!(word & 0xffULL))
	{
		word >>= 8;
		i++;
	}
	return (i);
}

void	*f_memchr(const void *s, int c, size_t n)
{
	uint64_t			pattern;
	uint64_t			word;
	uint64_t			matches;
	const unsigned char	*ptr;

	pattern = (uint64_t)(unsigned char)c * 0x0101010101010101ULL;
	ptr = s;
	while (n >= 8)
	{
		word = read_u64(ptr);
		word ^= pattern;
		matches = (word - 0x0101010101010101ULL)
			& ~word & 0x8080808080808080ULL;
		if (matches)
			return ((void *)(ptr + indexof_non_zero_byte(matches)));
		ptr += 8;
		n -= 8;
	}
	while (n--)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
