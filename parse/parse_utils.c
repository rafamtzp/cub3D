/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:46:17 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/09 17:31:18 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*Check the bonus cell map */
int	check_cell_bonus(t_data *data, char **map, int y, int x)
{
	if (ft_strchr("D0NSEW", map[y][x]))
	{
		if (check_adjacent_spaces(data, map, y, x) == FAILURE)
		{
			err_msg(NULL, "Map is open/not surrounded by walls", FAILURE);
			return (FAILURE);
		}
		if (ft_strchr("D", map[y][x]) && data->d_check == false)
			if (texture_door_filled(data) == FAILURE)
				return (FAILURE);
	}
	else if (!ft_strchr(" 01NSEWD", map[y][x]))
		return (err_msg(NULL, "Invalid character in map", FAILURE));
	return (SUCCESS);
}

/* Check if the texture is filled when we found a door */
int	texture_door_filled(t_data *data)
{
	data->d_check = true;
	if (!data->texinfo.door)
	{
		err_msg(NULL, "Missing texture door.", FAILURE);
		return (FAILURE);
	}
	return (SUCCESS);
}
