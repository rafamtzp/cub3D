/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:11:39 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/04 13:26:43 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Clear the current line and advance*/
static char	*clean_printed(char	*global_buffer)
{
	size_t	i;
	char	*new;
	size_t	j;

	i = 0;
	while (global_buffer[i] && global_buffer[i] != '\n')
		i++;
	if (!global_buffer[i])
	{
		free(global_buffer);
		return (NULL);
	}
	new = malloc(((ft_strlen(global_buffer) - i) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (global_buffer[i])
		new[j++] = global_buffer[i++];
	new[j] = '\0';
	free(global_buffer);
	return (new);
}

/*Get the current line*/
static char	*get_line(char *global_buffer)
{
	size_t	len;
	size_t	i;
	char	*line;

	len = 0;
	i = 0;
	if (!global_buffer[i])
		return (NULL);
	while (global_buffer[len] && global_buffer[len] != '\n')
		len++;
	line = malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (i <= len)
	{
		line[i] = global_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*Set the buffer.*/
static char	*join_n_free(char *global_buffer, char *local)
{
	size_t	len_global;
	size_t	len_local;
	char	*buffer;
	size_t	i;
	size_t	j;

	if (!global_buffer || !local)
		return (NULL);
	len_global = ft_strlen(global_buffer);
	len_local = ft_strlen(local);
	buffer = malloc((len_global + len_local + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len_global)
		buffer[i++] = global_buffer[j++];
	j = 0;
	while (j < len_local)
		buffer[i++] = local[j++];
	buffer[i] = '\0';
	free(global_buffer);
	return (buffer);
}

/*Read and save in a variable*/
static char	*read_buffsize(int fd, char *global_buffer)
{
	char	*buffer;
	int		bytes_rd;

	if (global_buffer == NULL)
		global_buffer = ft_gnl_calloc(1, sizeof(char));
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_rd = 1;
	while (bytes_rd > 0)
	{
		bytes_rd = read(fd, buffer, BUFFER_SIZE);
		if (bytes_rd == -1 || (bytes_rd == 0 && global_buffer == NULL))
		{
			free(global_buffer);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_rd] = '\0';
		global_buffer = join_n_free(global_buffer, buffer);
		if (ft_get_strchr(global_buffer, '\n'))
			break ;
	}
	free(buffer);
	return (global_buffer);
}

/*fd < 0 is invalid, same as buffer size*/
char	*get_next_line(int fd)
{
	static char	*global_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	global_buffer = read_buffsize(fd, global_buffer);
	if (!global_buffer)
		return (NULL);
	line = get_line(global_buffer);
	global_buffer = clean_printed(global_buffer);
	return (line);
}
