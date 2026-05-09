/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:27:04 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/09 17:26:05 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	*get_texture_pixels(void *img)
{
	int	*pixels;
	int	*img_data;
	int	bpp;
	int	size_line;
	int	endian;

	img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	pixels = ft_calloc(TEX_SIZE * TEX_SIZE, sizeof(int));
	if (!pixels)
		return (NULL);
	ft_memcpy(pixels, img_data, (TEX_SIZE * TEX_SIZE) * sizeof(int));
	return (pixels);
}

static int	init_pixel_buffer(t_data *data)
{
	data->win_img.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->win_img.img)
		return (FAILURE);
	data->win_img.buf = (uint32_t *)mlx_get_data_addr(data->win_img.img, &data->win_img.pixel_bits, &data->win_img.size_line, &data->win_img.endian);
	if (!data->win_img.buf)
		return (FAILURE);
	return (SUCCESS);
}

/* Loads one xpm texture and checks its dimensions */
static int	load_image(t_data *data, int i, char *path)
{
	int		width;
	int		height;
	void	*img;

	width = 0;
	height = 0;
	img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if (!img || width != TEX_SIZE || height != TEX_SIZE)
	{
		if (img)
			mlx_destroy_image(data->mlx, img);
		err_msg(path, "Failed to load texture or invalid size", FAILURE);
		return (FAILURE);
	}
	data->textures[i] = get_texture_pixels(img);
	mlx_destroy_image(data->mlx, img);
	if (!data->textures[i])
	{
		err_msg(path, "Failed to extract texture pixels", FAILURE);
		return (FAILURE);
	}
	return (SUCCESS);
}

/* Initialize and load all four textures (N, S, E, W) */
int	init_texture(t_data *data)
{
	char	*paths[4];
	int		i;

	paths[0] = data->texinfo.north;
	paths[1] = data->texinfo.south;
	paths[2] = data->texinfo.east;
	paths[3] = data->texinfo.west;
	data->textures = ft_calloc(5, sizeof(int *));
	if (!data->textures)
		return (err_msg(NULL, "Textures allocation failed", FAILURE));
	if (init_pixel_buffer(data) == FAILURE)
		return (err_msg(NULL, "Pixel buffer allocation failed", FAILURE));
	i = -1;
	while (++i < 4)
	{
		if (load_image(data, i, paths[i]) == FAILURE)
			return (FAILURE);
	}
	if (data->bonus && data->d_check)
	{
		i++;
		if (load_image(data, i, data->texinfo.door) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

/* Initialize texture info */
void	init_texinfo(t_texinfo *texture)
{
	texture->north = NULL;
	texture->south = NULL;
	texture->west = NULL;
	texture->east = NULL;
	texture->floor = -1;
	texture->ceiling = -1;
	texture->hex_floor = 0x0;
	texture->hex_ceiling = 0x0;
	texture->size = TEX_SIZE;
	texture->step = 0.0;
	texture->position = 0.0;
	texture->x = 0;
	texture->y = 0;
}
