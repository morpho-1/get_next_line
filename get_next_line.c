/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylemrab <aylemrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:35:38 by aylemrab          #+#    #+#             */
/*   Updated: 2023/01/28 15:49:15 by aylemrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_line(char *line)
{
	char	*str;
	int		i;

	i = 0;
	if (!line || !line[i])
		return (NULL);
	while (*(line + i) && *(line + i) != '\n')
		i ++;
	if (line[i] == '\n')
		str = malloc(sizeof(char) * (i + 2));
	else
		str = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (line[++i] && line[i] != '\n')
		str[i] = line[i];
	if (*(line + i) == '\n')
	{
		str[i] = line[i];
		i++;
	}
	return (str[i] = '\0', str);
}

static char	*ft_save(char *saving)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (saving[i] && saving[i] != '\n')
		i++;
	if (!saving[i])
		return (free(saving), NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(saving) - i + 1));
	if (!str)
		return (free(saving), NULL);
	i++;
	j = 0;
	while (*(saving + i))
		str[j++] = saving[i++];
	str[j] = '\0';
	free (saving);
	return (str);
}

static char	*ft_read(int fd, char *left_str)
{
	char	*buffer;
	int		i;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 1;
	while (!ft_strchr(left_str, '\n') && i != 0)
	{
		i = read (fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			if (left_str)
				free (left_str);
			free (buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		left_str = ft_strjoin(left_str, buffer);
	}
	free (buffer);
	return (left_str);
}

char	*get_next_line(int fd)
{
	static char	*left_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str = ft_read (fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_line (left_str);
	left_str = ft_save (left_str);
	return (line);
}
