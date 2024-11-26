/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agraille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:01:28 by agraille          #+#    #+#             */
/*   Updated: 2024/11/26 11:35:45 by agraille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcat(char *rest, char *buffer)
{
	size_t	j;

	j = 0;
	while (*rest)
		j++;
	while (*buffer)
		rest[j++] = *buffer++;
	return (rest);
}
