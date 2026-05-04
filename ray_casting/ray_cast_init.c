#include "../cub3d.h"

static double	absval(double x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

void	set_up_vectors(t_data *data, t_player *player, t_ray *ray, int x)
{
	// x-coordinate along the camera line and factor by which you scale plane from -1 to 1
	ray->camera_x = 2*x/(double)data->win_width - 1;
	// plane vector (perpendicular to dir)
	player->plane_x = player->dir_y;
	player->plane_y = -1 * player->dir_x;
	// ray direction
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	// player position in cell
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	// distance increments for ray scaled by 1/|raydir|
	ray->deltadist_x = absval(1 / ray->dir_x);
	ray->deltadist_y = absval(1 / ray->dir_y);
}

void	init_sidedists_and_steps(t_ray *ray, t_player *player)
{
	// determine step taken in the x and y directions and side_dists
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1 - player->pos_y) * ray->deltadist_y;
	}
}
