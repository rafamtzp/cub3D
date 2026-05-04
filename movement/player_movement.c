/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:35:57 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/04 16:36:01 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"


/* Update movement position and check wall colision */
static void	move_position(t_data *data, t_player *player)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = 0.01;
	new_x = player->pos_x;
	new_y = player->pos_y;
	if (player->move_y != 0)
	{
		new_x += player->dir_x * player->move_y * speed;
		new_y += player->dir_y * player->move_y * speed;
	}
	if (player->move_x != 0)
	{
		new_x += player->dir_y * player->move_x * speed;
		new_y += player->dir_x * player->move_x * speed;
	}
	if (data->map[(int)player->pos_y][(int)new_x] != '1')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_y] != '1')
		player->pos_y = new_y;
}

/* Update player position */
void	update_player(t_data *data)
{
	// if (data->player.rotate != 0)
	// 	rotate_player(&data->player, data->player.rotate);
	if (data->player.move_x != 0 || data->player.move_y != 0)
		move_position(data, &data->player);
}
