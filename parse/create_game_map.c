/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:49:16 by dperez-p          #+#    #+#             */
/*   Updated: 2026/04/21 14:50:17 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* fill the map leng to be equal and the height */
static int	fill_map_array(t_data *data, char **file, int i)
{
	int	row;
	int	col;

	row = 0;
	while (row < data->mapinfo.height)
	{
		data->map[row] = malloc(sizeof(char) * (data->mapinfo.width + 1));
		if (!data->map[row])
		{
			ft_free_matrix((void **)data->map);
			return (FAILURE);
		}
		ft_memset(data->map[row], ' ', data->mapinfo.width);
		data->map[row][data->mapinfo.width] = '\0';
		col = 0;
		while (file[i][col] && file[i][col] != '\n')
		{
			data->map[row][col] = file[i][col];
			col++;
		}
		i++;
		row++;
	}
	data->map[row] = NULL;
	return (SUCCESS);
}

/* Check if the line is completely blank or only spaces */
static int	is_line_empty(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (!ft_is_space(line[j]))
			return (0);
		j++;
	}
	return (1);
}

/* Count how many lines are from i index, stopping at an empty line */
static int	count_map_lines(char **file, int i)
{
	int	count;

	count = 0;
	while (file[i])
	{
		if (is_line_empty(file[i]))
			break ;
		i++;
		count++;
	}
	return (count);
}

/* Count the max width of the map until the calculated height */
static int	get_max_width(char **file, int i)
{
	int	max_w;
	int	len;
	int	n;

	max_w = 0;
	n = 0;
	while (file[i])
	{
		len = ft_strlen(file[i]);
		if (len > max_w)
		{
			max_w = len;
			n = i;
		}
		i++;
	}
	if (max_w > 0 && file[n][max_w - 1] == '\n')
		max_w--;
	return (max_w);
}

/* Start the map creatin getting the height and filling the array */
int	create_map(t_data *data, char **file, int i)
{
	data->mapinfo.height = count_map_lines(file, i);
	if (!data->mapinfo.height)
		return (err_msg(NULL, "Map height failed ", FAILURE));
	data->mapinfo.width = get_max_width(file, i);
	if (!data->mapinfo.width)
		return (err_msg(NULL, "Map width failed ", FAILURE));
	data->mapinfo.index_end_of_map = i + data->mapinfo.height;
	data->map = ft_calloc(data->mapinfo.height + 1, sizeof(char *));
	if (!data->map)
		return (err_msg(NULL, "Malloc map failed", FAILURE));
	if (fill_map_array(data, file, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
