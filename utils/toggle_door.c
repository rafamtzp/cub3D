/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 11:50:20 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/10 15:57:28 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Check the front of the view to close/open the door */
void	toggle_door(t_data *data)
{
	double	check_dist;
	int		target_x;
	int		target_y;
	char	cell;

	check_dist = 0.6;
	target_x = (int)(data->player.pos_x + data->player.dir_x * check_dist);
	target_y = (int)(data->player.pos_y + data->player.dir_y * check_dist);
	cell = data->map[target_y][target_x];
	if (cell == 'D')
		data->map[target_y][target_x] = 'O';
	else if (cell == 'O')
		data->map[target_y][target_x] = 'D';
}
