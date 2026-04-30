#include "../cub3d.h"

static double	absval(double x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

static void	set_up_vectors(t_data *data, t_player *player, t_ray *ray, int x)
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
	player->map_x = (int)player->pos_x;
	player->map_y = (int)player->pos_y;
	// distance increments for ray scaled by 1/|raydir|
	ray->deltadist_x = absval(1/ray->dir_x);
	ray->deltadist_y = ablsval(1/ray->dir_y);
}

static void	init_sidedists_and_steps(t_ray *ray, t_player *player)
{
	// determine step taken in the x and y directions and side_dists
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - player->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (player->map_x + 1 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - player->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y;
		ray->sidedist_y = (player->map_y + 1 - player->pos_y) * ray->deltadist_y;
	}
}

static double	dda_algo(t_data *data, t_player *player, t_ray *ray)
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

static void	calc_line_height(t_data *data, double perp_dist)
{
	data->line_height = (int)(data->win_height / perp_dist);
	data->draw_start = data->win_height / 2 - data->line_height / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + data->win_height / 2;
	if (data->draw_end >= data->win_height)
		data->draw_end = data->win_height - 1;
}

static void	texture_calculations(t_data *data, t_player *player, t_ray *ray, int perp_dist)
{
	t_texinfo tex;

	// calculate wall_x (proportional distance between lesser grid line and hit point)
	tex = data->texinfo;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + perp_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	// horizontal coord. on texture
	tex.x = (int)ray->wall_x * (double)tex.size;
	// need to get the distance from hit point to greater grid line in some cases
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex.x = tex.size - 1 - tex.x;
	// amount by which texture coord. increases per pixel on the screen
	tex.step = (double)tex.size / ray->line_height;
	tex.position = (ray->draw_start - data->win_height / 2 + data->line_height / 2) * tex.step;
}

static int	get_textype(t_ray ray)
{
	if (ray.dir_y < 0 && ray.side == 1)
		return (SOUTH);
	if (ray.dir_y > 0 && ray.side == 1)
		return (NORTH);
	if (ray.dir_x < 0 && ray.side == 0)
		return (WEST);
	if (ray.dir_x < 0 && ray.side == 0)
		return (EAST);
}

static void	copy_line_pixels(uint32_t *buffer, t_data *data, t_ray *ray)
{
	int y;
	int textype;
	t_texinfo tex;
	uint32_t color;

	tex = data->texinfo;
	textype = get_textype(*ray);
	y = data->draw_start;
	while (y < data->draw_end)
	{
		tex.y = (int)tex.position;
		tex.position += tex.step;
		color = data->textures[textype][]; // TODO
	}
}

void	ray_caster(t_data *data, t_player *player, t_ray *ray)
{
	double perp_dist;
	uint32_t buffer[data->texinfo.size][data->texinfo.size];
	int x;

	x = 0;
	while (x < data->win_width)
	{
		set_up_vectors(data, player, ray, x);
		init_sidedists_and_steps(ray, player);
		perp_dist = dda_algo(data, player, ray);
		calc_line_height(data, perp_dist);
		texture_calculations(data, player, ray, perp_dist);
		copy_line_pixels(data);
		x++;
	}
	draw_and_clear_buffer(&buffer, ); //TODO
}
