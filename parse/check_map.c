/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 09:30:58 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/09 16:53:00 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Check if is a transitable character or player next to a void space */
int	check_adjacent_spaces(t_data *data, char **map, int y, int x)
{
	if (y == 0 || y == data->mapinfo.height - 1
		|| x == 0 || x == data->mapinfo.width - 1)
		return (FAILURE);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (FAILURE);
	return (SUCCESS);
}

/* Check tif the character is valid, floor or its closed */
static int	check_cell(t_data *data, char **map, int y, int x)
{
	if (data->bonus)
	{
		if(check_cell_bonus(data, map, y, x) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	else
	{
		if (ft_strchr("0NSEW", map[y][x]))
		{
			if (check_adjacent_spaces(data, map, y, x) == FAILURE)
			{
				err_msg(NULL, "Map is open/not surrounded by walls", FAILURE);
				return (FAILURE);
			}
		}
		else if (!ft_strchr(" 01NSEW", map[y][x]))
			return (err_msg(NULL, "Invalid character in map", FAILURE));
		return (SUCCESS);
	}
}

/* Check characters, walls, and player info */
static int	validate_elements_and_walls(t_data *data, char **map)
{
	int	y;
	int	x;
	int	player;

	player = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				data->player.pos_x = (double)x + 0.5;
				data->player.pos_y = (double)y + 0.5;
				data->player.dir = map[y][x];
				player++;
			}
			if (check_cell(data, map, y, x) == FAILURE)
				return (FAILURE);
		}
	}
	if (player != 1)
		return (err_msg(NULL, "Map must have exactly one player", FAILURE));
	return (SUCCESS);
}

/* Check if we are at the end of the map */
static int	check_map_is_at_the_end(t_mapinfo *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

/* Validate the map and create with security */
int	validate_map(t_data *data, char **map_tab)
{
	if (!map_tab)
		return (err_msg(NULL, "Map pointer is NULL", FAILURE));
	if (data->mapinfo.height < 3)
		return (err_msg(NULL, "Map is too small", FAILURE));
	if (validate_elements_and_walls(data, map_tab) == FAILURE)
		return (FAILURE);
	if (check_map_is_at_the_end(&data->mapinfo) == FAILURE)
		return (err_msg(NULL, "Unexpected data after map content", FAILURE));
	return (SUCCESS);
}
