#include "../cub3d.h"

int	minimap_init(t_data *data)
{
	data->minimap.img = mlx_new_image(data->mlx, data->mapinfo.width * 16, data->mapinfo.height * 16);
	if (!data->minimap.img)
		return (FAILURE);
	data->minimap.buf = (uint32_t *)mlx_get_data_addr(data->minimap.img, &data->minimap.pixel_bits, &data->minimap.size_line, &data->minimap.endian);
	if (!data->minimap.buf)
		return (FAILURE);
	return (SUCCESS);
}

void	draw_minimap(t_data *data, t_img *minimap, t_player *player, char **map)
{
	int i;
	int j;

	if (!data->minimap_on)
		return ;
	i = 0;
	while (i < data->mapinfo.height * 16)
	{
		j = 0;
		while (j < minimap->size_line/4)
		{
			if ((int)(i/16) == (int)player->pos_y && (int)(j/16) == (int)player->pos_x)
				minimap->buf[i * minimap->size_line/4 + j] = 16711680;
			else if (map[(int)(i/16)][(int)(j/16)] == '1')
				minimap->buf[i * minimap->size_line/4 + j] = 16777212;
			else
				minimap->buf[i * minimap->size_line/4 + j] = 0;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, minimap->img, 
		 data->win_width - minimap->size_line/4, data->win_height - data->mapinfo.height * 16);
}
