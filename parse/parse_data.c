/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:52:32 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/11 18:04:39 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Get the total number of lines from the path */
static int	get_number_lines(char *path)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		err_msg(path, strerror(errno), errno);
		return (-1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

/* Fill the table with the map info moving firt on collums and then rows */
static void	fill_table(t_data *data)
{
	char	*line;
	int		row;

	row = 0;
	line = get_next_line(data->mapinfo.fd);
	while (line != NULL)
	{
		data->mapinfo.file[row] = ft_strdup(line);
		if (!(data->mapinfo.file[row]))
		{
			free(line);
			err_msg(NULL, "Could not allocate memory", 0);
			ft_free_matrix((void **)data->mapinfo.file);
			data->mapinfo.file = NULL;
			return ;
		}
		row++;
		free(line);
		line = get_next_line(data->mapinfo.fd);
	}
	data->mapinfo.file[row] = NULL;
}

/* Parse the data from the path to the struct to read */
void	parse_data(char *path, t_data *data)
{
	data->mapinfo.line_count = get_number_lines(path);
	if (data->mapinfo.line_count <= 0)
		return ;
	data->mapinfo.path = path;
	data->mapinfo.file = ft_calloc(data->mapinfo.line_count + 1,
			sizeof(char *));
	if (!(data->mapinfo.file))
	{
		err_msg(NULL, "Could not allocate memory", 0);
		return ;
	}
	data->mapinfo.fd = open(path, O_RDONLY);
	if (data->mapinfo.fd < 0)
	{
		free(data->mapinfo.file);
		data->mapinfo.file = NULL;
		err_msg(path, strerror(errno), 1);
		return ;
	}
	fill_table(data);
	close(data->mapinfo.fd);
}
