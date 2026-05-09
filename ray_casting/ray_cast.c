#include "../cub3d.h"

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

static void	texture_calculations(t_data *data, t_player *player, t_ray *ray, double perp_dist)
{
	t_texinfo *tex;

	// calculate wall_x (proportional distance between lesser grid line and hit point)
	tex = &data->texinfo;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + perp_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	// horizontal coord. on texture
	tex->x = (int)(ray->wall_x * TEX_SIZE);
	// need to get the distance from hit point to greater grid line in some cases
	// NEGATED THIS TO FLIP TEXTURES! 5/5/26
	if (!(ray->side == 0 && ray->dir_x > 0) && !(ray->side == 1 && ray->dir_y < 0))
		tex->x = TEX_SIZE - 1 - tex->x;
	// amount by which texture coord. increases per pixel on the screen
	tex->step = (double)TEX_SIZE / data->line_height;
	tex->position = (data->draw_start - data->win_height / 2 + data->line_height / 2) * tex->step;
}

static int	get_textype(t_ray ray)
{
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

static void	copy_pixel_column(t_img *img, t_data *data, t_ray *ray, int x)
{
	int y;
	int textype;
	t_texinfo tex;
	uint32_t color;

	tex = data->texinfo;
	textype = get_textype(*ray);
	y = 0;
	// draw ceiling
	while (y < data->draw_start)
	{
		img->buf[y * img->size_line/4 + x] = (uint32_t)data->texinfo.ceiling; // hex floor is a different data type but let's see what happens
		y++;
	}
	//printf("PASSED CEILING LOOP\n");
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
		img->buf[y * img->size_line/4 + x] = color;
		y++;
	}
	//draw floor
	while (y < data->win_height)
	{
		img->buf[y * img->size_line/4 + x] = (uint32_t)data->texinfo.floor;
		y++;
	}
}

void	ray_cast(t_data *data, t_player *player, t_ray *ray)
{
	double perp_dist;
	int x;

	x = 0;
	while (x < data->win_width)
	{
		set_up_vectors(data, player, ray, x);
		init_sidedists_and_steps(ray, player);
		perp_dist = dda_algo(data, ray);
		calc_line_height(data, perp_dist);
		texture_calculations(data, player, ray, perp_dist);
		copy_pixel_column(&data->win_img, data, ray, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->win_img.img, 0, 0);
	if (data->bonus)
		draw_minimap(data, &data->minimap, &data->player, data->map);
}
