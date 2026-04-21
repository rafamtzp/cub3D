/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 11:12:47 by dperez-p          #+#    #+#             */
/*   Updated: 2026/04/18 20:32:25 by dperez-p         ###   ########.fr       */
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
	if (data->textures)
		ft_free_matrix((void **)data->textures);
	if (data->texture_pixels)
		ft_free_matrix((void **)data->texture_pixels);
	free_texinfo(&data->texinfo);
	free_map(data);
	return (1);
}
