/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/12/01 23:23:13 by agraille         ###   ########.fr       */
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
	size_t		remaining_len;
	char		*newline_pos;

	check = *buffer;
	len_malloc = 0;
	while (check)
	{
		newline_pos = ft_strchr(check->content, '\n');
		if (newline_pos)
		{
			len_malloc += (newline_pos - check->content + 1);
			break ;
		}
		len_malloc += ft_strlen(check->content);
		check = check->next;
	}
	line = ft_copy(line, len_malloc, buffer);
	if (newline_pos)
	{
		remaining_len = ft_strlen(newline_pos + 1);
		ft_memmove((*buffer)->content, newline_pos + 1, remaining_len + 1);
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
	static t_chain			*buffer;
	char					*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		if (!ft_add_node(&buffer))
			return (NULL);
	}
	line = NULL;
	if (ft_check_if_line_possible(buffer))
		line = ft_extract_line(&buffer, line);
	else
	{
		if (ft_read_and_stock(fd, &buffer) == -1)
			return (NULL);
		line = ft_extract_line(&buffer, line);
	}
	return (line);
}

// int main(void)
// {
// 	int fd;
// 	char *test;
// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{ 
// 		perror("open");
// 		return (1);
// 	}
// 		test = get_next_line(fd);
// 		printf("LINE : %s", test); 
// 		free(test);
// 	printf("---------------------------------\n");
// 			test = get_next_line(fd);
// 		printf("LINE : %s", test); 
// 		free(test);
// 	printf("---------------------------------\n");
// 		test = get_next_line(fd);
// 		printf("LINE : %s", test); 
// 		free(test);
// 	printf("---------------------------------\n");
// 	close(fd); 
// 	return (0); 
// }
