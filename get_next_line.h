/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:01:25 by agraille          #+#    #+#             */
/*   Updated: 2024/11/27 23:04:40 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2

# endif

char	*ft_strchr(char *s, int c);
void	ft_free_chain(t_chain **buffer);

typedef struct s_gnl
{
	char			content[BUFFER_SIZE + 1];
	char			*cut_pos;
	struct s_gnl	*next;
}	t_chain;

#endif

