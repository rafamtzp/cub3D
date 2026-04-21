/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:38:10 by dperez-p          #+#    #+#             */
/*   Updated: 2026/04/21 19:20:20 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* initialize mlx and the mlx window */
void init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		clean_and_exit(data, err_msg("mlx", "Could not initialize mlx", 1));
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
		clean_and_exit(data, err_msg("mlx", "Could not create mlx window", 1));
}
