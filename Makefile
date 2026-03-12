NAME := so_long

CC := cc
CFLAGS := -Wall -Wextra -Werror -std=gnu89

RM := rm -rf
MAKEFLAGS += --no-print-directory

OBJ_DIR := build
SRC_DIR := source
INC_DIR := include
MLX_DIR := mlx
LIBFT_DIR := libft

MLX := ./mlx/libmlx_Linux.a
LIBFT := ./libft/libft.a
LIBS := $(MLX) -L/usr/lib/X11 -lXext -lX11 -lm $(LIBFT)
INCLUDES = -I/usr/include -I./mlx -I./libft/include -I./include

SRC_MAIN := main free_memory exit_error test_utils

SRC_MAP := \
	map/map_init \
	map/map_checker

SRC_A_STAR := \
	a_star/a_star \
	a_star/a_star_utils \
	a_star/a_star_list \
	a_star/a_star_cell_details \
	a_star/a_star_struct \
	a_star/a_star_free_memory

SRC_GAME := \
	game/game \
	game/free_game \
	game/game_init

SRC_TEXTURE := \
	game/textures/set_textures \
	game/textures/print_image \
	game/textures/combine_image \
	game/textures/combine_image_utils \
	game/textures/set_walls_coins_ennemies \
	game/textures/set_textures_others \
	game/textures/set_textures_player \
	game/textures/free_textures

SRC_HUD := \
	game/hud/hud \
	game/hud/hud_swords \
	game/hud/hud_health \
	game/hud/hud_utils

SRC_UPDATE := \
	game/update/update \
	game/update/update_index

SRC_PLAYER := \
	game/player/player \
	game/player/player_print \
	game/player/player_utils

SRC_COLLECTIBLE := \
	game/collectible/collectibles \
	game/collectible/collectible_print \
	game/collectible/collectible_print_move

SRC_SWORD := \
	game/sword/sword_update \
	game/sword/sword_list \
	game/sword/sword_print \
	game/sword/sword_utils

SRC_ENNEMY := \
	game/ennemy/ennemy_list \
	game/ennemy/ennemy_update \
	game/ennemy/ennemy_print \
	game/ennemy/ennemy_print_move

SRC_WINDOW := \
	game/window/init_window \
	game/window/screen_array

SRC_START_MLX := \
	start_mlx/mlx_routine \
	start_mlx/start_mlx \
	start_mlx/worker_routine \
	start_mlx/worker

SRCS := \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_MAIN))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_MAP))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_A_STAR))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_GAME))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_TEXTURE))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_HUD))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_UPDATE))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_PLAYER))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_COLLECTIBLE))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_SWORD))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_ENNEMY))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_WINDOW))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_START_MLX)))

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	@echo "Linking $(NAME)"
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(MLX):
	@echo "Building mlx"
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	@echo "Building libft"
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -g -c -o $@ $<

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

norm:
	norminette $(SRC_DIR) $(INC_DIR)

.PHONY: all clean fclean re norm

-include $(DEPS)