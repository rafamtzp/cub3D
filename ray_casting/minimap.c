/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 18:20:19 by ramarti2          #+#    #+#             */
/*   Updated: 2026/05/13 15:53:54 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	minimap_init(t_data *data)
{
	data->minimap.img = mlx_new_image(data->mlx, data->mapinfo.width * 16,
			data->mapinfo.height * 16);
	if (!data->minimap.img)
		return (FAILURE);
	data->minimap.buf = (uint32_t *)mlx_get_data_addr(data->minimap.img,
			&data->minimap.pixel_bits, &data->minimap.size_line,
			&data->minimap.endian);
	if (!data->minimap.buf)
		return (FAILURE);
	return (SUCCESS);
}

static void	draw_minimap_tile(t_data *data, t_img *minimap, int i, int j)
{
	if ((int)(i / 16) == (int)data->player.pos_y && (int)(j
			/ 16) == (int)data->player.pos_x)
		minimap->buf[i * minimap->size_line / 4 + j] = MM_RED;
	else if (data->map[(int)(i / 16)][(int)(j / 16)] == '1')
		minimap->buf[i * minimap->size_line / 4 + j] = MM_WHITE;
	else if (data->map[(int)(i / 16)][(int)(j / 16)] == 'D')
		minimap->buf[i * minimap->size_line / 4 + j] = MM_BROWN;
	else if (data->map[(int)(i / 16)][(int)(j / 16)] == 'O')
		minimap->buf[i * minimap->size_line / 4 + j] = MM_DARK_GRAY;
	else
		minimap->buf[i * minimap->size_line / 4 + j] = MM_BLACK;
}

void	draw_minimap(t_data *data, t_img *minimap)
{
	int	i;
	int	j;

	if (!data->minimap_on)
		return ;
	i = 0;
	while (i < data->mapinfo.height * 16)
	{
		j = 0;
		while (j < minimap->size_line / 4)
		{
			draw_minimap_tile(data, minimap, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, minimap->img, data->win_width
		- minimap->size_line / 4, data->win_height - data->mapinfo.height * 16);
}
