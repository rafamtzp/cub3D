#include "../cub3d.h"

double	dda_algo(t_data *data, t_player *player, t_ray *ray)
{
	int is_hit;

	is_hit = 0;
	while (is_hit = 0)
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
		if (data->map[ray->map_x][ray->map_y] == '1')
			is_hit = 1;
	}
	if (ray->side == 0)
		return (ray->sidedist_x - ray->deltadist_x);
	return (ray->sidedist_y - ray->deltadist_y);
}