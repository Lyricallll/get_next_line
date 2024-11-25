/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:01:26 by agraille          #+#    #+#             */
/*   Updated: 2024/11/25 16:39:12 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"

size_t	get_next_line(int fd)
{
	char			*buffer;
	static char		*temp;
	size_t			oc_read;

	if (fd < 0)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	oc_read = read(fd, buffer, BUFFER_SIZE);
	if (oc_read == -1)
		return (0);
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
