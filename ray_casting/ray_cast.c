/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 18:21:05 by ramarti2          #+#    #+#             */
/*   Updated: 2026/05/11 18:44:29 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	draw_backdrops(t_img *img, t_data *data, int x, int y)
{
	if (y == 0)
	{
		while (y < data->draw_start)
		{
			img->buf[y * img->size_line / 4
				+ x] = (uint32_t)data->texinfo.ceiling;
			y++;
		}
		return (y);
	}
	while (y < data->win_height)
	{
		img->buf[y * img->size_line / 4 + x] = (uint32_t)data->texinfo.floor;
		y++;
	}
	return (y);
}

static void	copy_pixel_column(t_img *img, t_data *data, t_ray *ray, int x)
{
	int			y;
	int			textype;
	t_texinfo	tex;
	uint32_t	color;

	tex = data->texinfo;
	textype = get_textype(data, *ray, data->player);
	y = draw_backdrops(img, data, x, 0);
	while (y < data->draw_end)
	{
		tex.y = (int)tex.position;
		if (tex.y >= TEX_SIZE)
			tex.y = TEX_SIZE - 1;
		else if (tex.y < 0)
			tex.y = 0;
		tex.position += tex.step;
		color = data->textures[textype][TEX_SIZE * tex.y + tex.x];
		if (ray->side == 0)
			color = (color >> 1) & 8355711;
		img->buf[y * img->size_line / 4 + x] = color;
		y++;
	}
	draw_backdrops(img, data, x, y);
}

void	ray_cast(t_data *data, t_player *player, t_ray *ray)
{
	int	x;

	x = 0;
	while (x < data->win_width)
	{
		set_up_vectors(data, player, ray, x);
		init_sidedists_and_steps(ray, player);
		dda_algo(data, ray);
		calc_line_height(data, ray->perp_dist);
		texture_calculations(data, player, ray, ray->perp_dist);
		copy_pixel_column(&data->win_img, data, ray, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->win_img.img, 0, 0);
	if (data->bonus)
		draw_minimap(data, &data->minimap, &data->player, data->map);
}
