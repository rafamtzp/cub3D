/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:27:43 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/04 16:54:29 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "./libft_complete/ft_libft/libft.h"
# include "colors.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>


/***************************** MACROS *****************************/

# define WIN_HEIGHT 480
# define WIN_WIDTH 640

# define TEX_SIZE 64

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

/***************************** ERROR_MESSAGE *****************************/
# define ERROR_USAGE "usage: ./cub3d <path/to/map.cub>"

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

/***************************** STRUCTS *****************************/

typedef struct s_img
{
	void	*img;
	uint32_t		*buf; // changed int * to uint32_t *
	// also changed name from address to buf
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_textinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				floor;
	int				ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			position;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_minimap
{
	char	**map;
	t_img	*img;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
}	t_minimap;

typedef struct s_mapinfo
{
	int		fd;
	int		line_count;
	char	*path;
	char	**file;
	int		height;
	int		width;
	int		index_end_of_map;
}	t_mapinfo;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_mapinfo	mapinfo;
	char		**map;
	t_player	player;
	t_ray		ray;
	t_img		win_img;
	int			**textures;
	t_texinfo	texinfo;
	t_img		minimap;
	t_keys		keys;
}	t_data;



/***************************** FUNCTIONS *****************************/

int	err_msg(char *detail, char *str, int code);

/* init */
void	init_data(t_data *data);
void	init_texinfo(t_texinfo *texture);
void	init_img_clean(t_img *img);
void	init_ray_clean(t_ray *ray);
int		init_texture(t_data *data);
void	init_mlx(t_data *data);
void	init_player_direction(t_data *data);

/* exit */
void	clean_and_exit(t_data *data, int code);
int	quit_cub3d(t_data *data);
int	free_data(t_data *data);

/* parse */
int	check_file(char	*ag, bool cub);
void	parse_data(char *path, t_data *data);
int	process_file_data(t_data *data, char **map);
int	fill_color_textures(t_texinfo *textures, char *line, int j);
int	create_map(t_data *data, char **file, int i);
int	validate_map(t_data *data, char **map_tab);
int	validate_textures(t_data *data, t_texinfo *textures);

/* movement */
void	wait_for_input(t_data *data);
void	update_player(t_data *data);

/* ray casting */
void	ray_cast(t_data *data, t_player *player, t_ray *ray);
double	dda_algo(t_data *data, t_ray *ray);
void	set_up_vectors(t_data *data, t_player *player, t_ray *ray, int x);
void	init_sidedists_and_steps(t_ray *ray, t_player *player);

#endif
