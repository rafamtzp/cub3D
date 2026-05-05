/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:37:28 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/05 17:04:49 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	update_axis_values(t_data *data)
{
	data->player.move_y = data->keys.w - data->keys.s;
	data->player.move_x = data->keys.a - data->keys.d;
	data->player.rotate = data->keys.right - data->keys.left;
}

/* Key press handler */
static int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_Left)
		data->keys.left = 1;
	if (key == XK_Right)
		data->keys.right = 1;
	if (key == XK_w)
		data->keys.w = 1;
	if (key == XK_a)
		data->keys.a = 1;
	if (key == XK_s)
		data->keys.s = 1;
	if (key == XK_d)
		data->keys.d = 1;
	update_axis_values(data);
	return (0);
}

/* Key release handler */
static int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_w)
		data->keys.w = 0;
	if (key == XK_s)
		data->keys.s = 0;
	if (key == XK_a)
		data->keys.a = 0;
	if (key == XK_d)
		data->keys.d = 0;
	if (key == XK_Left)
		data->keys.left = 0;
	if (key == XK_Right)
		data->keys.right = 0;
	update_axis_values(data);
	return (0);
}

/* Input for mlx loop */
void	wait_for_input(t_data *data)
{
	mlx_hook(data->win, ClientMessage, NoEventMask, quit_cub3d, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press_handler, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release_handler, data);
}
