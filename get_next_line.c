/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/12/03 10:29:02 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check_if_line_possible(t_chain *buffer)
{
	t_chain	*check;

	check = buffer;
	while (check)
	{
		if (ft_strchr(check->content, '\n'))
		{
			return (1);
		}
		check = check->next;
	}
	return (0);
}

char	*ft_extract_line(t_chain **buffer, char *line)
{
	t_chain		*check;
	size_t		len;
	char		*n_pos;

	check = *buffer;
	len = 0;
	n_pos = NULL;
	while (check)
	{
		n_pos = ft_strchr(check->content, '\n');
		if (n_pos)
		{
			len += (n_pos - check->content + 1);
			break ;
		}
		len += ft_strlen(check->content);
		check = check->next;
	}
	line = ft_copy(line, len, buffer, 0);
	if (n_pos)
	{
		ft_memmove((*buffer)->content, n_pos + 1, ft_strlen(n_pos + 1) + 1);
	}
	return (line);
}

t_chain	*ft_add_node(t_chain **buffer)
{
	t_chain	*current;
	t_chain	*new_node;

	if (!buffer)
		return (NULL);
	current = *buffer;
	while (current && current->next != NULL)
		current = current->next;
	new_node = (t_chain *)malloc(sizeof(t_chain));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->content[0] = '\0';
	if (current)
		current->next = new_node;
	else
		*buffer = new_node;
	return (new_node);
}

ssize_t	ft_read_and_stock(int fd, t_chain **buffer)
{
	t_chain	*current;
	ssize_t	readed;

	current = *buffer;
	readed = 1;
	while (readed > 0)
	{
		if (current->content[0] != '\0')
		{
			if (!ft_add_node(buffer))
				return (-1);
			current = current->next;
		}
		readed = read(fd, current->content, BUFFER_SIZE);
		if (readed > 0)
		{
			current->content[readed] = '\0';
			if (ft_strchr(current->content, '\n'))
				break ;
			if (!ft_add_node(buffer))
				return (-1);
			current = current->next;
		}
	}
	return (readed);
}

char	*get_next_line(int fd)
{
	static t_chain	*buffer;
	char			*line;
	ssize_t			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || (!buffer && !ft_add_node(&buffer)))
		return (NULL);
	line = NULL;
	if (!ft_check_if_line_possible(buffer))
	{
		i = ft_read_and_stock(fd, &buffer);
		if (i <= 0)
		{
			if (i == 0 && buffer && buffer->content[0] != '\0')
				line = ft_extract_line(&buffer, line);
			ft_free_chain(&buffer);
			return (line);
			if (i == -1)
			{
				ft_free_chain(&buffer);
				return (NULL);
			}
		}
	}
	line = ft_extract_line(&buffer, line);
	return (line);
}
