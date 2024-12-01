/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/12/01 15:30:47 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_check_if_line_possible(t_chain **buffer, int fd)
{
    t_chain *check;
    t_chain *original;

    original = *buffer;
    check = *buffer;
    while (check)
    {
        if (ft_strchr(check->content, '\n'))
        {
            return (1);
        }
        check = check->next;
    }

    check = (t_chain *)malloc(sizeof(t_chain));
    if (!check)
        return (-1);
	check->next = NULL;
    check->content[0] = '\0';

    *buffer = original;
    printf("Content: %s\n", (*buffer)->content);
    return (fd);
}


char	*ft_extract_line(t_chain **buffer, char *line, int fd)
{
	t_chain		*check;
	ssize_t		len_malloc;
	size_t 		remaining_len;
	char		*newline_pos;
	
	if (!ft_check_if_line_possible(buffer, fd))
		return (NULL);
	check = *buffer;
	len_malloc = 0;
	while (check)
	{
		newline_pos = ft_strchr(check->content, '\n');
		if (newline_pos)
		{
			len_malloc += (newline_pos - check->content + 1);
			break;
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
	// printf("BUFFER TETE DE LISTE APRES EXTRACT LINE= %s\n\n",(*buffer)->content);
	return (line);
}


t_chain	*ft_add_node(t_chain **buffer)
{
	t_chain *current;

	if (!buffer)
		return (NULL);
	current = *buffer;
	while (current && current->next != NULL)
		current = current->next;

	t_chain *new_node = (t_chain *)malloc(sizeof(t_chain));
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



ssize_t ft_read_and_stock(int fd, t_chain **buffer)
{
    t_chain *current;
    ssize_t readed;

    current = *buffer;
    readed = 1;
    while (readed > 0)
    {
        readed = read(fd, current->content, BUFFER_SIZE);
        if (readed > 0)
        {
            current->content[readed] = '\0';
            if (ft_strchr(current->content, '\n'))
                break;
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
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		if(!ft_add_node(&buffer))
			return (NULL);
	}
	if (buffer->content[0] == '\0')
	{
		if (ft_read_and_stock(fd, &buffer) == -1)
			return (NULL);
	}
	line = NULL;
	line = ft_extract_line(&buffer, line, fd);
	return (line);
}

int main(void)
{
	int fd;
	char *test;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{ 
		perror("open");
		return (1);
	}
		test = get_next_line(fd);
		printf("LINE : %s", test); 
		free(test);
	printf("---------------------------------\n");
			test = get_next_line(fd);
		printf("LINE : %s", test); 
		free(test);
	printf("---------------------------------\n");
		// test = get_next_line(fd);
		// printf("LINE : %s", test); 
		// free(test);
	// printf("---------------------------------\n");
	close(fd); 
	return (0); 
}

