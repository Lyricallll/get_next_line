/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/26 11:31:09 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"

static char	*rest_reset(char *rest)
{
	rest = NULL;
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*temp;
	static char		*rest;
	size_t			oc_read;

	if (fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	oc_read = read(fd, buffer, BUFFER_SIZE);
	if (oc_read == -1 || oc_read == 0)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (temp);
}

int	main (void)
{
	int	fd = open("test.txt", O_RDONLY);

	printf("%s",get_next_line(fd));
	close(fd);
	return (0);
}
