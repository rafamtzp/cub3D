#include "../cub3d.h"

void	minimap_init(t_data *data)
{
	data->minimap.img = mlx_new_image(data->mlx, data->mapinfo.width * 4, data->mapinfo.height * 4);
	data->minimap.buf = mlx_get_data_addr(data->minimap.img, &data->minimap.pixel_bits, &data->minimap.size_line, &data->minimap.endian);
}

void	draw_minimap(t_data *data, char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		data->minimap
		i++;
	}
}