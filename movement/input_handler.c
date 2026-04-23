/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:37:28 by dperez-p          #+#    #+#             */
/*   Updated: 2026/04/23 19:06:23 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_keys	g_keys;

static void	update_axis_values(t_data *data)
{
	data->player.move_y = g_keys.w - g_keys.s;
	data->player.move_x = g_keys.d - g_keys.a;
	data->player.rotate = g_keys.right - g_keys.left;
}

/* Key press handler */
static int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_Left)
		g_keys.left = 1;
	if (key == XK_Right)
		g_keys.right = 1;
	if (key == XK_w)
		g_keys.w = 1;
	if (key == XK_a)
		g_keys.a = 1;
	if (key == XK_s)
		g_keys.s = 1;
	if (key == XK_d)
		g_keys.d = 1;
	update_axis_values(data);
	return (0);
}

/* Key release handler */
static int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_w)
		g_keys.w = 0;
	if (key == XK_s)
		g_keys.s = 0;
	if (key == XK_a)
		g_keys.a = 0;
	if (key == XK_d)
		g_keys.d = 0;
	if (key == XK_Left)
		g_keys.left = 0;
	if (key == XK_Right)
		g_keys.right = 0;
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
