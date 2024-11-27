/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/27 09:00:47 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"

int	ft_init(t_chain **buffer)
{
	if (!*buffer)
	{
		*buffer = (t_chain *)malloc(sizeof(t_chain));
		if (!*buffer)
			return (0);
		// (*buffer)->content = NULL;
		(*buffer)->next = NULL;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_chain	*buffer;
	char			*line;
	size_t			readed;//voir pour ssize

	if (!ft_init(&buffer))
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		//tout free
		return (NULL);
	readed = 1;
	while (readed > 0)
	{
		//check si quelaue chose a lire 
		//si oui mettre dans le buffer read 
		//readed = \n && \0 malloc ma line pour la return 
		// stock le surplus de \n reset buffer 
		
	}
	// rajouter la fonction qui free si read = 0
	return (line);
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);

	printf("%s",get_next_line(fd));
	close(fd);
	return (0);
}
