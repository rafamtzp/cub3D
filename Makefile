NAME = cub3D

CC = cc
CFLAGS = -Wall -Werror -Wextra -std=gnu99

# Directories
MINILIBX_DIR = minilibx-linux
LIBFT_DIR = libft_complete

# Libraries
MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a
LIBFT = $(LIBFT_DIR)/libft.a

# Includes
INCLUDES = -I. -I$(MINILIBX_DIR) -I$(LIBFT_DIR)
LIBS = -L$(MINILIBX_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lft -lXext -lX11 -lm

# Source files
SRCS = main.c \
	error/error.c \
	exit/exit.c \
	exit/free_data.c \
	init/init.c \
	init/init_texture.c \
	init/init_mlx.c \
	parse/check_args.c \
	parse/check_map.c \
	parse/check_textures.c \
	parse/create_game_map.c \
	parse/fill_color_textures.c \
	parse/parse_data.c \
	parse/process_file_data.c \
	movement/input_handler.c \
	movement/player_movement.c\
	ray_casting/dda_algo.c \
	ray_casting/ray_cast_init.c \
	ray_casting/ray_cast.c \
	ray_casting/minimap.c \
	init/init_player_dir.c \

# Files without bonus
SRC_NB = 	utils/utils.c

# Bonus source files
SRCS_B = bonus/utils_bonus.c

# Object files
OBJS = $(SRCS:.c=.o)

# Objet without bonus
OBJS_NB = $(SRC_NB:.c=.o)

# Bonus object files
OBJS_B = $(SRCS_B:.c=.o)

# Rules
all: $(MINILIBX) $(LIBFT) $(NAME)

$(MINILIBX):
	@make -C $(MINILIBX_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_NB) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(OBJS) $(OBJS_B)
	@make -C $(MINILIBX_DIR)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_B) $(LIBS) -o $(NAME)

clean:
	@make clean -C $(MINILIBX_DIR)
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@rm -f $(OBJS_NB)
	@rm -f $(OBJS_B)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@rm -f $(OBJS_NB)
	@rm -f $(OBJS_B)

re: fclean all

.PHONY: all clean fclean re bonus
