/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:35:57 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/06 12:28:37 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

static int	is_valid_pos(t_data *data, double x, double y)
{
	double	margin;

	margin = 0.2;
	if (data->map[(int)(y - margin)][(int)(x - margin)] == '1')
		return (0);
	if (data->map[(int)(y - margin)][(int)(x + margin)] == '1')
		return (0);
	if (data->map[(int)(y + margin)][(int)(x - margin)] == '1')
		return (0);
	if (data->map[(int)(y + margin)][(int)(x + margin)] == '1')
		return (0);
	return (1);
}

/* Update movement position and check wall colision */
static void	move_position(t_data *data, t_player *player)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = 0.005;
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
		new_y += -1 * player->dir_x * player->move_x * speed;
	}
	if (is_valid_pos(data, new_x, player->pos_y))
		player->pos_x = new_x;
	if (is_valid_pos(data, player->pos_x, new_y))
		player->pos_y = new_y;
}

static void	rotate_player(t_player *player)
{
	double rotspeed;
	double old_dir_x;

	if (player->rotate != 0)
	{
		rotspeed = 0.01 * player->rotate;
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rotspeed) - player->dir_y * sin(rotspeed);
		player->dir_y = old_dir_x * sin(rotspeed) + player->dir_y * cos(rotspeed);  
	}
}

/* Update player position */
void	update_player(t_data *data)
{
	if (data->player.rotate != 0)
	 	rotate_player(&data->player);
	if (data->player.move_x != 0 || data->player.move_y != 0)
		move_position(data, &data->player);
}
