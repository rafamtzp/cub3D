/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 12:55:54 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/09 17:26:20 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Validate the the textures to be fill and the RGB*/
int	validate_textures(t_data *data, t_texinfo *textures)
{
	(void)data;
	if (!textures->north || !textures->south
		|| !textures->east || !textures->west)
		return (err_msg(NULL, "Missing wall textures", FAILURE));
	if (check_file(textures->north, false) == FAILURE
		|| check_file(textures->south, false) == FAILURE
		|| check_file(textures->west, false) == FAILURE
		|| check_file(textures->east, false) == FAILURE)
		return (FAILURE);
	if (textures->floor == -1 || textures->ceiling == -1)
		return (err_msg(NULL, "Missing floor or ceiling colors", FAILURE));
	if (data->bonus && data->d_check)
	{
		if (check_file(textures->door, false) == FAILURE)
			return (err_msg(NULL, "Missing door textures", FAILURE));
	}
	return (SUCCESS);
}
