/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaukes <jaukes@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/11/26 01:12:21 by jaukes        #+#    #+#                 */
/*   Updated: 2026/11/26 01:12:21 by jaukes        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_state	t_state;

struct s_state
{
	char	buf[BUFFER_SIZE];
	size_t	i;
	ssize_t	n;
	int		fd;
	t_state	*next;
};

typedef struct s_string
{
	char	*buf;
	size_t	len;
	size_t	cap;
}			t_string;

char	*get_next_line(int fd);

int		string_push(t_string *str, char c);

char	*string_resize_fit(t_string *str);

#endif
