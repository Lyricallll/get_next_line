/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:01:25 by agraille          #+#    #+#             */
/*   Updated: 2024/11/30 15:01:28 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 70
# endif

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}	t_chain;

ssize_t ft_strchr(char *s, int c);
void	ft_free_chain(t_chain **buffer);
ssize_t	ft_strlen(char *s);
char	*ft_copy(char *line, ssize_t len_malloc, t_chain **buffer);
void	*ft_memmove(void *dest, const void *src, ssize_t n);
ssize_t ft_read_and_stock(int fd, t_chain **buffer);

#endif

