NAME = so_long
SRC_DIR = source
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
	game/free_game.c							\
	game/game_init.c							\
	game/hud/hud.c								\
	game/hud/hud_swords.c						\
	game/hud/hud_health.c						\
	game/hud/hud_utils.c						\
	game/update/update_index.c					\
	game/update/update.c						\
	game/player/player.c						\
	game/player/player_print.c					\
	game/player/player_utils.c					\
	game/collectible/collectibles.c				\
	game/collectible/collectible_print.c		\
	game/collectible/collectible_print_move.c	\
	game/sword/sword_update.c					\
	game/sword/sword_list.c						\
	game/sword/sword_print.c					\
	game/sword/sword_utils.c					\
	game/ennemy/ennemy_list.c					\
	game/ennemy/ennemy_update.c					\
	game/ennemy/ennemy_print.c					\
	game/ennemy/ennemy_print_move.c				\
	game/window/screen_array.c					\
	game/window/init_window.c					\
	game/textures/set_textures.c				\
	game/textures/print_image.c					\
	game/textures/combine_image.c				\
	game/textures/combine_image_utils.c			\
	game/textures/set_walls_coins_ennemies.c	\
	game/textures/set_textures_others.c			\
	game/textures/set_textures_player.c			\
	game/textures/free_textures.c				\
	free_memory.c								\
	error.c 									\
	test_utils.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = build
C_FLAGS = -Werror -Wextra -Wall
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
INCLUDES = -I/usr/include -Imlx -Ilibft/include -Iinclude
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFTPRINTF_LIB = $(LIBFTPRINTF_DIR)/libftprintf.a
LIBFTPRINTF_DIR = libftprintf
CHECK_SYSTEM = config.txt
DEP = $(OBJ:.o=.d)

all: $(MLX_LIB) $(LIBFTPRINTF_LIB) $(OBJ_DIR) $(NAME)

norminette:
	clear
	norminette $(SRC_DIR) $(INCLUDE_DIR)

$(NAME): $(OBJS) $(LIBFTPRINTF_LIB)
	$(CC) $(C_FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFTPRINTF_LIB) $(INCLUDES)

$(MLX_LIB):
	make --no-print-directory -C $(MLX_DIR)

$(LIBFTPRINTF_LIB):
	make -C $(LIBFTPRINTF_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $< into $@"
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(INCLUDES) -MMD -MP -g -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -fr $(OBJ_DIR)
	@make clean --no-print-directory -C $(LIBFTPRINTF_DIR)

fclean:
	@rm -fr $(OBJ_DIR) $(NAME)
	@make fclean --no-print-directory -C $(LIBFTPRINTF_DIR)

re: fclean all

-include $(DEP)
