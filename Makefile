NAME = a.out
SRC_DIR = src
SRCS = main.c map/map_init.c map/map_checker.c free_memory.c \
	test_utils.c collectibles.c a_star/a_star.c a_star/a_star_utils.c \
	a_star/a_star_list.c  a_star/a_star_cell_details.c a_star/a_star_struct.c \
	game/game.c a_star/a_star_free_memory.c game/window/init_screen_array.c game/textures/set_textures.c \
	game/window/init_window.c game/window/utils_window.c game/textures/combine_image.c \
	game/textures/print_image.c

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

$(NAME): $(OBJS) $(LIBFTPRINTF_LIB) $(HEADER) $(MLX_LIB) $(CHECK_SYSTEM) 
	$(CC) $(C_FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFTPRINTF_LIB)

$(CHECK_SYSTEM):
	xrandr | awk '/ connected primary/ {print $$4}' > $(CHECK_SYSTEM)

$(MLX_LIB):
	@make --no-print-directory -C $(MLX_DIR)

$(LIBFTPRINTF_LIB):
	make -C $(LIBFTPRINTF_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	@$(CC) $(C_FLAGS) -c -o $@ $< $(INCLUDES)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/map
	mkdir -p $(OBJ_DIR)/a_star
	mkdir -p $(OBJ_DIR)/game
	mkdir -p $(OBJ_DIR)/game/textures
	mkdir -p $(OBJ_DIR)/game/window

clean:
	@rm -fr $(OBJ_DIR) $(CHECK_SYSTEM)
	@make clean --no-print-directory -C $(LIBFTPRINTF_DIR)

fclean:
	@rm -fr $(OBJ_DIR) $(NAME) $(CHECK_SYSTEM)
	@make fclean --no-print-directory -C $(LIBFTPRINTF_DIR)

