NAME = a.out
SRC_DIR = src
SRCS = main.c									\
	map/map_init.c								\
	map/map_checker.c							\
	a_star/a_star.c								\
	a_star/a_star_utils.c						\
	a_star/a_star_list.c						\
	a_star/a_star_cell_details.c				\
	a_star/a_star_struct.c						\
	a_star/a_star_free_memory.c					\
	game/game.c									\
	game/player.c								\
	game/collectibles.c							\
	game/window/screen_array.c					\
	game/window/init_window.c					\
	game/textures/set_textures.c				\
	game/textures/print_image.c					\
	game/textures/combine_image.c				\
	game/textures/combine_image_utils.c			\
	game/textures/set_textures_wallls_coins.c	\
	free_memory.c								\
	test_utils.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = $(SRC_DIR)/obj
C_FLAGS = -Werror -Wextra -Wall
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
INCLUDE_DIR = include
INCLUDES = -I/usr/include -Imlx -Ilibft/include
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
HEADER = include/so_long.h
LIBFTPRINTF_LIB = $(LIBFTPRINTF_DIR)/libftprintf.a
LIBFTPRINTF_DIR = libftprintf
CHECK_SYSTEM = config.txt

all: $(MLX_LIB) $(LIBFTPRINTF_LIB) $(NAME)

norminette:
	norminette $(SRC_DIR) $(INCLUDE_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFTPRINTF_LIB) $(HEADER) $(MLX_LIB) 
	$(CC) $(C_FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFTPRINTF_LIB)

$(MLX_LIB):
	make --no-print-directory -C $(MLX_DIR)

$(LIBFTPRINTF_LIB):
	make -C $(LIBFTPRINTF_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(C_FLAGS) -c -o $@ $< $(INCLUDES)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/map
	mkdir -p $(OBJ_DIR)/a_star
	mkdir -p $(OBJ_DIR)/game
	mkdir -p $(OBJ_DIR)/game/textures
	mkdir -p $(OBJ_DIR)/game/window

clean:
	@rm -fr $(OBJ_DIR)
	@make clean --no-print-directory -C $(LIBFTPRINTF_DIR)

fclean:
	@rm -fr $(OBJ_DIR) $(NAME)
	@make fclean --no-print-directory -C $(LIBFTPRINTF_DIR)

