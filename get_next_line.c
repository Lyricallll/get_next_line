/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/26 08:38:22 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*temp;
	size_t			oc_read;

	if (fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	oc_read = read(fd, buffer, BUFFER_SIZE);
	if (oc_read == -1 && oc_read == 0)
		return (NULL);
	free(buffer);
	return (oc_read);
}
int	main (void)
{
    int fd = open("test.txt", O_RDONLY);
    size_t oc_read;
	
    while ((oc_read = get_next_line(fd)) > 0)
    {
        printf("Bytes read: %zu\n", oc_read);
    }
    close(fd);
    return (0);
}
