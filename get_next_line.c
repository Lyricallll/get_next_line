/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/12/02 15:55:05 by agraille         ###   ########.fr       */
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
	ssize_t		len_malloc;
	char		*n_pos;

	check = *buffer;
	len_malloc = 0;
	n_pos = NULL;
	while (check)
	{
		n_pos = ft_strchr(check->content, '\n');
		if (n_pos)
		{
			len_malloc += (n_pos - check->content + 1);
			break ;
		}
		len_malloc += ft_strlen(check->content);
		check = check->next;
	}
	line = ft_copy(line, len_malloc, buffer);
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (!buffer && !ft_add_node(&buffer))
		return (NULL);
	if (!ft_check_if_line_possible(buffer))
	{
		if (ft_read_and_stock(fd, &buffer) <= 0)
		{
			if (buffer && buffer->content[0] != '\0')
				line = ft_copy(line, ft_strlen(buffer->content), &buffer);
			ft_free_chain(&buffer);
			return (line);
		}
	}
	line = ft_extract_line(&buffer, line);
	if (!line || line[0] == '\0')
	{
		ft_free_chain(&buffer);
		return (NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("43_no_nl.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
