/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:35:57 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/15 17:10:08 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Check if the position is a wall */
static int	is_valid_pos(t_data *data, double x, double y)
{
	double	radius;

	radius = 0.2;
	if (data->map[(int)(y - radius)][(int)(x - radius)] == '1'
		|| data->map[(int)(y - radius)][(int)(x - radius)] == 'D')
		return (0);
	if (data->map[(int)(y - radius)][(int)(x + radius)] == '1'
		|| data->map[(int)(y - radius)][(int)(x + radius)] == 'D')
		return (0);
	if (data->map[(int)(y + radius)][(int)(x - radius)] == '1'
		|| data->map[(int)(y + radius)][(int)(x - radius)] == 'D')
		return (0);
	if (data->map[(int)(y + radius)][(int)(x + radius)] == '1'
		|| data->map[(int)(y + radius)][(int)(x + radius)] == 'D')
		return (0);
	return (1);
}

/* Update movement position and check wall collision */
static void	move_position(t_data *data, t_player *player)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = 0.03;
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

static void	rotate_player(t_player *player, double rot_amount)
{
	double	rotspeed;
	double	old_dir_x;

	if (rot_amount != 0)
	{
		rotspeed = 0.03 * rot_amount;
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rotspeed) - player->dir_y
			* sin(rotspeed);
		player->dir_y = old_dir_x * sin(rotspeed) + player->dir_y
			* cos(rotspeed);
	}
}

static void	process_mouse_rotation(t_data *data)
{
	double	delta_x;
	double	rot_amount;

	if (!data->win)
		return ;
	delta_x = data->player.mouse_x - (WIN_WIDTH / 2.0);
	if (delta_x != 0)
	{
		rot_amount = delta_x * MOUSE_SENS * 2;
		rotate_player(&data->player, rot_amount);
	}
	mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	data->player.mouse_x = (double)(WIN_WIDTH / 2);
	data->player.mouse_y = (double)(WIN_HEIGHT / 2);
}

/* Update player position */
void	update_player(t_data *data)
{
	if (data->bonus && data->mouse_locked)
		process_mouse_rotation(data);
	if (data->player.rotate != 0)
		rotate_player(&data->player, data->player.rotate);
	if (data->player.move_x != 0 || data->player.move_y != 0)
		move_position(data, &data->player);
}
