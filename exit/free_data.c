/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 11:12:47 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/01 15:18:15 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Frees map data and closes the file descriptor */
static void	free_map(t_data *data)
{
	if (data->mapinfo.fd > 0)
	{
		close(data->mapinfo.fd);
		data->mapinfo.fd = -1;
	}
	if (data->mapinfo.file)
		ft_free_matrix((void **)data->mapinfo.file);
	if (data->map)
		ft_free_matrix((void **)data->map);
}

/* Free the texture info */
static void	free_texinfo(t_texinfo *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
}

/* Clean the texture matrix and pixel buffer */
int	free_data(t_data *data)
{
	int	i;

	if (data->textures)
	{
		i = 0;
		while (i < 4)
		{
			if (data->textures[i])
				free(data->textures[i]);
			i++;
		}
		free(data->textures);
		data->textures = NULL;
	}
	// if (data->texture_pixels) // not using texture_pixels
	// 	ft_free_matrix((void **)data->texture_pixels);
	// data->texture_pixels = NULL;
	// Rafa's version:
	if (data->win_img.buf)
		mlx_destroy_image(data->mlx, data->win_img.buf);

	free_texinfo(&data->texinfo);
	free_map(data);
	return (1);
}
