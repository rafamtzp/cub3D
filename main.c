/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:24:21 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/13 16:08:12 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_controls(t_data *data)
{
	printf(BRIGHT_YELLOW "\n");
	printf("░█▀▀░█░█░█▀▄░▀▀█░█▀▄░░░█▀▀░█▀█░█▀█░▀█▀░█▀▄░█▀█░█░░░█▀▀\n");
	printf("░█░░░█░█░█▀▄░░▀▄░█░█░░░█░░░█░█░█░█░░█░░█▀▄░█░█░█░░░▀▀█\n");
	printf("░▀▀▀░▀▀▀░▀▀░░▀▀░░▀▀░░░░▀▀▀░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀\n");
	printf(RESET "\n");
	printf(BRIGHT_YELLOW "\tW" RESET ": move forward\t");
	printf(BRIGHT_YELLOW "\tS" RESET ": move backward\n");
	printf(BRIGHT_YELLOW "\tA" RESET ": strafe left\t");
	printf(BRIGHT_YELLOW "\tD" RESET ": strafe right\n");
	printf(BRIGHT_YELLOW "\t← " RESET ": rotate left\t");
	printf(BRIGHT_YELLOW "\t→ " RESET ": rotate right\n");
	if (data->bonus)
	{
		printf(BRIGHT_YELLOW "\tM " RESET ": Show/Hide map");
		printf(BRIGHT_YELLOW "\tZ" RESET ": Lock/Unlock Mouse\n");
	}
	printf("\n");
}

/* Check for validations and parse args untill player direction */
static int	parse_args(t_data *data, char **argv)
{
	if (check_file(argv[1], true) == 1)
		clean_and_exit(data, 1);
	parse_data(argv[1], data);
	if (process_file_data(data, data->mapinfo.file) == FAILURE)
		return (free_data(data));
	if (validate_map(data, data->map) == FAILURE)
		return (free_data(data));
	if (validate_textures(data, &data->texinfo) == FAILURE)
		return (free_data(data));
	init_player_direction(data);
	return (0);
}

int	render_frame(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	update_player(data);
	ray_cast(data, &data->player, &data->ray);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (err_msg("Usage", ERROR_USAGE, 1));
	init_data(&data);
	if (parse_args(&data, argv) != 0)
		return (1);
	init_mlx(&data);
	if (init_texture(&data) == FAILURE)
		clean_and_exit(&data, FAILURE);
	if (data.bonus)
	{
		if (minimap_init(&data) == FAILURE)
			clean_and_exit(&data, FAILURE);
		if (data.mouse_locked)
			mlx_mouse_hide(data.mlx, data.win);
	}
	print_controls(&data);
	wait_for_input(&data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
