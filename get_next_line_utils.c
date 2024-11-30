/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:01:28 by agraille          #+#    #+#             */
/*   Updated: 2024/11/30 11:47:03 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

void	ft_free_chain(t_chain **buffer)
{
	t_chain	*tmp;

	while (*buffer)
	{
		tmp = (*buffer)->next;
		free(*buffer);
		*buffer = tmp;
	}
	*buffer = NULL;
}

ssize_t	ft_strlen(char *s)
{
	ssize_t	i;
	
	i = 0;
	while(s[i])
	{
		if (s[i] == '\n' )
		{
			i += 1;
			break;
		}
		i++;
	}
	return (i);
}

char	*ft_copy(char *line, ssize_t len_malloc, t_chain **buffer)
{
	t_chain	*ptr;
	ssize_t	i;
	ssize_t	j;
	
	i = 0;
	j = 0;
	ptr = *buffer;
	line = malloc(sizeof(char) * (len_malloc + 1));
	if (!line)
		return (NULL);
	while (i < len_malloc)
	{
		line[i++] = ptr->content[j++];
		if (ptr->content[j] == '\0')
		{
			if(ptr->next == NULL)
				break;
			j = 0;
			ptr = ptr->next;
		}
	}
	line[i] = '\0';
	return (line);
}

void	*ft_memmove(void *dest, const void *src, ssize_t n)
{
	unsigned char			*dest_copy;
	const unsigned char		*src_copy;
	ssize_t					i;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_copy = (unsigned char *)dest;
	src_copy = (const unsigned char *)src;
	if (dest_copy > src_copy)
	{
		i = n;
		while (i-- > 0)
			dest_copy[i] = src_copy[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest_copy[i] = src_copy[i];
			i++;
		}
	}
	return (dest);
}
