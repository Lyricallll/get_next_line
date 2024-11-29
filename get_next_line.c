/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/29 11:16:04 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(t_chain **buffer, char *line)
{
	t_chain		*count_len;
	t_chain 	*for_copy;
	ssize_t		len_malloc;
	
	len_malloc = 1;
	count_len = *buffer;
	for_copy = *buffer;
	while (count_len != NULL)
	{
		len_malloc += count_len->len;
		count_len = count_len->next;
	}
	printf("LA LEN EST DE : %zd\n",len_malloc);
	// line = malloc(sizeof(char) * len_malloc + 1);
	// line[len_malloc] = '\0';
	return (line);
}

int	ft_init(t_chain **buffer)
{
	if (!*buffer)
	{
		*buffer = (t_chain *)malloc(sizeof(t_chain));
		if (!*buffer)
			return (0);
		(*buffer)->cut_pos = NULL;
		(*buffer)->next = NULL;
		(*buffer)->len = 0;
		(*buffer)->content[0] = '\0';
	}
    return (1);
}

ssize_t	ft_read_and_stock(int fd, t_chain **buffer)
{
	t_chain	*current;
	ssize_t	readed;

	current = *buffer;
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, current->content, BUFFER_SIZE);
		if (readed > 0)
		{
			current->content[readed] = '\0';
			current->len = readed;
			current->cut_pos = ft_strchr(current->content, '\n');
			if (current->cut_pos)
				break;
			if (!current->cut_pos)
			{
				current->next = (t_chain *)malloc(sizeof(t_chain));
				if (!current->next)
					return (0);
				current = current->next;
				current->cut_pos = NULL;
				current->next = NULL;
				current->len = 0;
				current->content[0] = '\0';
			}
		}
	}
	return (readed);
}

char	*get_next_line(int fd)
{	
	static t_chain	*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || !ft_init(&buffer))
		return (NULL);
	if (!ft_read_and_stock(fd, &buffer))
		return (NULL);
	line = NULL;
	line = ft_extract_line(&buffer, line);
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
    // t_chain *ptr;
    // t_chain *current;
	char	*test;

    fd = open("test.txt", O_RDONLY);
    // if (fd < 0)
    //     return (1);

    // // Lire la liste + compter les nodes
    // ptr = get_next_line(fd);
    // if (!ptr)
    //     return (printf("ptr null"));
    // current = ptr;
	// int i = 1;
    // while (current)
    // {
	// 	printf("NODE = %d\n",i);
    //     printf("%s\n", current->content);
	// 	i++;
    //     current = current->next;      
    // }
    // ft_free_chain(&ptr);


	test = get_next_line(fd);
	if (test == NULL)
		printf("La line est null\n");
	free(test);
    close(fd);
    return (0);
}

