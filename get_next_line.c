/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/27 23:17:27 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(t_chain **buffer)
{
	// Combiner le contenu des nœuds jusqu'à '\n' ou NULL
	// Libérer les nœuds déjà utilisés
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
    return (1);
	}
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
			current->cut_pos = strchr(current->content, '\n');
				// break;
			if (!current->cut_pos)
			{
				current->next = (t_chain *)malloc(sizeof(t_chain));
				if (!current->next)
					return;
				current = current->next;
				current->cut_pos = NULL;
				current->next = NULL;
			}
		}
	}
	return (readed);
}

char	*get_next_line(int fd)
{	static t_chain	*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || !ft_init(&buffer))
		return (NULL);
	if (!ft_read_and_stock(fd, &buffer))
		return (NULL); // revoir cette condition pour gerer 
						//la fin de fichier et le read -1
	line = ft_extract_line(&buffer);
	if (line[0] == 0)
	{
		free(line);
		ft_free_chain(buffer);
		return(NULL);
	}
	return (line);
}
