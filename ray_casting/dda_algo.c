/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/9 16:21:31 by ramarti2          #+#    #+#             */
/*   Updated: 2026/05/11 18:10:44 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	dda_algo(t_data *data, t_ray *ray)
{
	ray->is_hit = 0;
	while (ray->is_hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if ((data->bonus && data->map[ray->map_y][ray->map_x] == 'D') ||
		(data->map[ray->map_y][ray->map_x] == '1'))
			ray->is_hit = 1;
	}
	if (ray->side == 0)
		ray->perp_dist = ray->sidedist_x - ray->deltadist_x;
	else
		ray->perp_dist = ray->sidedist_y - ray->deltadist_y;
	if (ray->perp_dist < 0.0001)
		ray->perp_dist = 0.0001;
}
