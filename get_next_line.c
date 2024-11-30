/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/30 22:12:21 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_update_buffer(t_chain **buffer)
{
	t_chain *current;
	char *newline_pos;

	current = *buffer;
	newline_pos = ft_strchr(current->content, '\n');
	if (newline_pos)
		ft_memmove(current->content, newline_pos + 1, ft_strlen(newline_pos + 1) + 1);
	else
		current->content[0] = '\0';
}

char	*ft_extract_line(t_chain **buffer, char *line)
{
	// t_chain		*current;
	t_chain		*check;
	ssize_t		len_malloc;

	// current = *buffer;
	check = *buffer;
	printf("CHECk = %s",check->content);
	len_malloc = 0;
	 while (check)
    {
        len_malloc += ft_strlen(check->content);
		printf("%ld = LEN MALLOC\n",len_malloc);
        // if (ft_strchr(check->content, '\n'))
        //     break;
        check = check->next;
    }
	printf("%ld = LEN MALLOC\n",len_malloc);
	line = ft_copy(line, len_malloc, buffer);
	return (line);
}


t_chain *ft_add_node(t_chain **buffer)
{
    t_chain *current;
    t_chain *new_node;

    if (!buffer)
        return (NULL);
    current = *buffer;
    if (!current)
    {
        new_node = (t_chain *)malloc(sizeof(t_chain));
        if (!new_node)
            return (NULL);
        new_node->next = NULL;
        new_node->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (!new_node->content)
        {
            free(new_node);
            return (NULL);
        }
        new_node->content[0] = '\0';
        *buffer = new_node;
        return (new_node);
    }
    while (current->next != NULL)
        current = current->next;
    new_node = (t_chain *)malloc(sizeof(t_chain));
    if (!new_node)
        return (NULL);
    new_node->next = NULL;
    new_node->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!new_node->content)
    {
        free(new_node);
        return (NULL);
    }
    new_node->content[0] = '\0';
    current->next = new_node;
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
            printf("Current node : %s\n", current->content);
            if (ft_strchr(current->content, '\n'))
                break;
            if (!ft_add_node(buffer))
                return (-1);
			if (!current->content)
                return (-1);
			current = current->next;
        }
    }
	printf("BFER = %s",(*buffer)->content);
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
	line = ft_extract_line(&buffer, line);
	ft_free_chain(&buffer);
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
		test = get_next_line(fd);
		printf("LINE : %s", test); 
		free(test);
	printf("---------------------------------\n");
	close(fd); 
	return (0); 
}

