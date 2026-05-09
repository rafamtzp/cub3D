/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_door_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:21:19 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/09 15:59:40 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Check if the texture is duplicate and if not parse the info */
int	fill_door_texture(t_texinfo *texture, char *line, int j)
{
	if (line[j] == 'D' && line[j + 1] == 'O')
	{
		if (texture->door != NULL)
			return (err_msg("Door", "Duplicate texture", 1));
		texture->door = get_texture_path(line, j + 4);
	}

	return (0);
}
