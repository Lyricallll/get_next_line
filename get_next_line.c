/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:00:05 by agraille          #+#    #+#             */
/*   Updated: 2024/11/30 11:55:16 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_chain	*ft_reset_from_cut(t_chain **head)
{
	t_chain	*tmp;
	ssize_t	remaining_len;

	// Si cut_pos est trouvé
	if (*head && (*head)->cut_pos)
	{
		// Vérifiez si le '\n' est présent dans le cut_pos
		if ((*head)->cut_pos[0] == '\n')
		{
			// Si cut_pos pointe directement sur '\n', nous devons avancer à l'élément suivant
			tmp = (*head)->next;
			free(*head);  // Libérer l'élément courant
			*head = tmp;  // Passer au suivant
		}
		else
		{
			// Calculer la longueur des données restantes après le '\n'
			remaining_len = ft_strlen((*head)->cut_pos + 1);

			// Déplacer le contenu restant vers le début du tableau
			ft_memmove((*head)->content, (*head)->cut_pos + 1, remaining_len);

			// Réinitialiser cut_pos à NULL pour signaler qu'il n'y a plus de '\n' dans cette chaîne
			// (*head)->cut_pos = NULL;
		}
	}
	return (tmp);
}



char	*ft_extract_line(t_chain **buffer, char *line)
{
	t_chain		*count_len;
	ssize_t		len_malloc;
	
	len_malloc = 0;
	count_len = *buffer;
	line = NULL;
	while (count_len != NULL)
	{
		len_malloc += ft_strlen(count_len->content);
			count_len = count_len->next;
	}
	line = ft_copy(line, len_malloc, buffer);
	//sauvegarder apres le \n et reset la chaine 
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		if(!ft_init(&buffer))
			return (NULL);
	}
	if (ft_read_and_stock(fd, &buffer) == -1)
		return (NULL);
	line = NULL;
	line = ft_extract_line(&buffer, line);
	if (line == NULL)
	{
		ft_free_chain(&buffer);
		return(NULL);
	}printf("AVANT LA MISE A JOUR = %s\n",buffer->content);
	printf("---------------------------\n");
	buffer = ft_reset_from_cut(&buffer);
	printf("APRES LA MISE A JOUR = %s\n",buffer->content);
	printf("---------------------------\n");
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
	printf("1 : %s",test);
	free(test);
	// printf("---------------------------\n");
	// test = get_next_line(fd);
	// printf("2 : %s",test);
	// free(test);
    close(fd);
    return (0);
}

