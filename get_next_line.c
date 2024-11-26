/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/26 17:06:12 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"

int	ft_init(t_list **buffer)
{
	if (!*buffer)
	{
		*buffer = (t_list *)malloc(sizeof(t_list));
		if (!*buffer)
			return (0);
		(*buffer)->content = NULL;
		(*buffer)->next = NULL;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*buffer;
	char			*line;
	size_t			readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (ft_init(&buffer))
		return (NULL);
	return (line);
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);

	printf("%s",get_next_line(fd));
	close(fd);
	return (0);
}
