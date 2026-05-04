/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:24:21 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/04 16:28:03 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_controls(void)
{
	printf(CYAN "\n");
	printf("░█▀▀░█░█░█▀▄░▀▀█░█▀▄░░░█▀▀░█▀█░█▀█░▀█▀░█▀▄░█▀█░█░░░█▀▀\n");
	printf("░█░░░█░█░█▀▄░░▀▄░█░█░░░█░░░█░█░█░█░░█░░█▀▄░█░█░█░░░▀▀█\n");
	printf("░▀▀▀░▀▀▀░▀▀░░▀▀░░▀▀░░░░▀▀▀░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀\n");
	printf(RESET "\n");
	printf(CYAN "\tW" RESET ": move forward\t");
	printf(CYAN "\tS" RESET ": move backward\n");
	printf(CYAN "\tA" RESET ": strafe left\t");
	printf(CYAN "\tD" RESET ": strafe right\n");
	printf(CYAN "\t← " RESET ": rotate left\t");
	printf(CYAN "\t→ " RESET ": rotate right\n");
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

static int	render_frame(void *param)
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
	print_controls();
	wait_for_input(&data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
