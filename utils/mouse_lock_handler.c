/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_lock_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:24:21 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/09 15:07:59 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Toggle mouse lock */
void	mouse_lock_handler(t_data *data)
{
	data->mouse_locked = !data->mouse_locked;
	if (data->mouse_locked)
		mlx_mouse_hide(data->mlx, data->win);
	else
		mlx_mouse_show(data->mlx, data->win);
}
