/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:01:28 by agraille          #+#    #+#             */
/*   Updated: 2024/12/03 09:31:22 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

void	ft_free_chain(t_chain **buffer)
{
	t_chain	*tmp;

	while (*buffer)
	{
		tmp = (*buffer)->next;
		ft_memmove((*buffer)->content, 0, 0);
		free(*buffer);
		*buffer = NULL;
		*buffer = tmp;
	}
	*buffer = NULL;
}

ssize_t	ft_strlen(char *s)
{
	ssize_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_copy(char *line, size_t len, t_chain **buffer, size_t j)
{
	t_chain	*ptr;
	t_chain	*tmp;
	size_t	i;

	i = 0;
	ptr = *buffer;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (i < len)
	{
		if (ptr->content[j] == '\0')
		{
			if (ptr->next == NULL)
				break ;
			j = 0;
			tmp = ptr;
			ptr = ptr->next;
			*buffer = ptr;
			free(tmp);
		}
		line[i++] = ptr->content[j++];
	}
	line[i] = '\0';
	return (line);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*dest_copy;
	const unsigned char		*src_copy;
	size_t					i;

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
