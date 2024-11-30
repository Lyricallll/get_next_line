/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/30 15:00:16 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(t_chain **buffer, char *line, int fd)
{
	t_chain		*current;
	ssize_t		len_malloc;
	
	len_malloc = 0;
	current = *buffer;
	while (current != NULL)
	{
		if (ft_strchr(current->content, '\n'))
			break;
		else
			{
				current->next = (t_chain *)malloc(sizeof(t_chain));
            if (!current->next)
                return (NULL);
            current = current->next;
            current->next = NULL;
            current->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
			if (!current->content)
                return (NULL);
			current->content[0] = '\0';
			len_malloc += ft_read_and_stock(fd, &current);
			}
	}
	len_malloc = ft_strlen(current->content);
	line = ft_copy(line, len_malloc, buffer);
	return (line);
}

int	ft_init(t_chain **buffer)
{
	if (!*buffer)
	{
		*buffer = (t_chain *)malloc(sizeof(t_chain));
		if (!*buffer)
			return (0);
		(*buffer)->next = NULL;
		(*buffer)->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*buffer)->content)
            return (0);
        (*buffer)->content[0] = '\0';
	}
    return (1);
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
            current->next = (t_chain *)malloc(sizeof(t_chain));
            if (!current->next)
                return (-1);
            current = current->next;
            current->next = NULL;
            current->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
			if (!current->content)
                return (-1);
			current->content[0] = '\0';
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
	if (!buffer)
	{
		if(!ft_init(&buffer))
			return (NULL);
	}
	if (buffer->content[0] == '\0')
	{
		if (ft_read_and_stock(fd, &buffer) == -1)
			return (NULL);
	}
	line = NULL;
	line = ft_extract_line(&buffer, line, fd);
	if (line == NULL)
	{
		ft_free_chain(&buffer);
		return(NULL);
	}
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
	if (test == NULL) 
	printf("La ligne est null\n"); 
	else printf("1 : %s", test); 
	printf("------------------------------\n");
	free(test); 
	test = get_next_line(fd); 
	if (test == NULL) printf("La ligne est null\n"); 
	else printf("2 : %s", test); 
	printf("------------------------------\n");
	free(test); 
	test = get_next_line(fd); 
	if (test == NULL) printf("La ligne est null\n"); 
	else printf("3 : %s", test); 
	printf("------------------------------\n");
	free(test); 
	close(fd); 
	return (0); 
}

