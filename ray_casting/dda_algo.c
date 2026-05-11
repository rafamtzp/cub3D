#include "../cub3d.h"

double	dda_algo(t_data *data, t_ray *ray)
{
	int is_hit;
	double perp_dist;

	is_hit = 0;
	while (is_hit == 0)
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
			is_hit = 1;
	}
	if (ray->side == 0)
		perp_dist = ray->sidedist_x - ray->deltadist_x;
	else
		perp_dist = ray->sidedist_y - ray->deltadist_y;
	if (perp_dist < 0.0001)
		perp_dist = 0.0001;
	return (perp_dist);
}
