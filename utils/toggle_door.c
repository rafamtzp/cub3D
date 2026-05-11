/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 11:50:20 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/11 17:24:39 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_not_in_door(t_data *data, double x, double y)
{
	double	radius;

	radius = 0.2;
	if (data->map[(int)(y - radius)][(int)(x - radius)] == 'O')
		return (0);
	if (data->map[(int)(y - radius)][(int)(x + radius)] == 'O')
		return (0);
	if (data->map[(int)(y + radius)][(int)(x - radius)] == 'O')
		return (0);
	if (data->map[(int)(y + radius)][(int)(x + radius)] == 'O')
		return (0);
	return (1);
}

/* Check the front of the view to close/open the door */
void	toggle_door(t_data *data)
{
	double	check_dist;
	int		target_x;
	int		target_y;
	char	cell;

	check_dist = 1;
	target_x = (int)(data->player.pos_x + data->player.dir_x * check_dist);
	target_y = (int)(data->player.pos_y + data->player.dir_y * check_dist);
	cell = data->map[target_y][target_x];
	if (cell == 'D')
		data->map[target_y][target_x] = 'O';
	else if (cell == 'O')
	{
		if (is_not_in_door(data, data->player.pos_x, data->player.pos_y))
			data->map[target_y][target_x] = 'D';
	}
}
