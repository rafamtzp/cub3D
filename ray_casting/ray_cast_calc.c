/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 18:23:50 by ramarti2          #+#    #+#             */
/*   Updated: 2026/05/11 18:24:44 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_line_height(t_data *data, double perp_dist)
{
	data->line_height = (int)(data->win_height / perp_dist);
	data->draw_start = data->win_height / 2 - data->line_height / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + data->win_height / 2;
	if (data->draw_end >= data->win_height)
		data->draw_end = data->win_height - 1;
}

void	texture_calculations(t_data *data, t_player *player, t_ray *ray,
		double perp_dist)
{
	t_texinfo	*tex;

	tex = &data->texinfo;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + perp_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	tex->x = (int)(ray->wall_x * TEX_SIZE);
	if (!(ray->side == 0 && ray->dir_x > 0) && !(ray->side == 1
			&& ray->dir_y < 0))
		tex->x = TEX_SIZE - 1 - tex->x;
	tex->step = (double)TEX_SIZE / data->line_height;
	tex->position = (data->draw_start - data->win_height / 2 + data->line_height
			/ 2) * tex->step;
}

int	get_textype(t_data *data, t_ray ray, t_player player)
{
	int	pos_y;
	int	pos_x;

	pos_y = (int)(player.pos_y + ray.dir_y * (ray.perp_dist + 0.01));
	pos_x = (int)(player.pos_x + ray.dir_x * (ray.perp_dist + 0.01));
	if (data->bonus && data->map[pos_y][pos_x] == 'D')
		return (DOOR);
	if (ray.dir_y > 0 && ray.side == 1)
		return (SOUTH);
	if (ray.dir_y < 0 && ray.side == 1)
		return (NORTH);
	if (ray.dir_x < 0 && ray.side == 0)
		return (WEST);
	if (ray.dir_x > 0 && ray.side == 0)
		return (EAST);
	return (FAILURE);
}
