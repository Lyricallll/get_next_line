/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/27 14:41:45 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// fonction qui free toute la chaine 

int	ft_init(t_chain **buffer)
{
	 t_chain	*current;
	 
	if (!*buffer)
	{
		*buffer = (t_chain *)malloc(sizeof(t_chain));
		if (!*buffer)
			return (0);
		(*buffer)->next = NULL;
    current = *buffer;
    while (current->next != NULL)
    {
        current = current->next;
    }
	current->next = (t_chain *)malloc(sizeof(t_chain));
    if (!current->next)
        return (0);
    current->next->next = NULL;
	}
    return (1);
}

void	ft_read_and_stock(int fd, t_chain **buffer)
{
	ssize_t			readed;
	
	readed = 1;
	while (readed == 1)
	{
		readed = read(fd, (*buffer)->content, BUFFER_SIZE);
		if (readed > 0)
		{
			//check si \n trouve 
			// new node
			*buffer = (*buffer)->next;
		}
		//if 0 fin de fichier et free tout print le restant du buffer 
		//if -1 exit fast 
	}
}

char	*get_next_line(int fd)
{	static t_chain	*buffer;
	char			*line;

	if (!ft_init(&buffer))
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		//tout free
		return (NULL);
	ft_read_and_stock(fd, &buffer);
	line = 'l' ;//remplir en liberant les node
	return (NULL);
}

// int	main(void)
// {
// 	int	fd = open("test.txt", O_RDONLY);

// 	printf("%s",get_next_line(fd));
// 	close(fd);
// 	return (0);
// }
