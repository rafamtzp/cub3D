/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 20:09:45 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/11 17:57:25 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Init base data */
void	init_data(t_data *data)
{
	set_bonus(&data->bonus);
	data->mlx = NULL;
	data->win = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	init_player(&data->player);
	init_keys(&data->keys);
	init_texinfo(&data->texinfo);
	data->map = NULL;
	init_mapinfo(&data->mapinfo);
	if (data->bonus)
	{
		init_img_clean(&data->minimap);
		data->minimap_on = 0;
	}
	data->textures = NULL;
	data->d_check = false;
}
