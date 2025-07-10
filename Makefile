NAME = so_long
CC = cc
CFLAGS = -Werror -Wextra -Wall

OBJECTS_DIR = build
INCLUDE_DIR = include
MLX_DIR = mlx
LIBFT_DIR = libft

SOURCE_DIR = source
SOURCES_MAIN = main free_memory exit_error test_utils

MAP_DIR = $(SOURCE_DIR)/map
SOURCES_MAP = map_init	map_checker

A_STAR_DIR = $(SOURCE_DIR)/a_star
SOURCES_A_STAR = a_star a_star_utils a_star_list \
	a_star_cell_details a_star_struct a_star_free_memory

GAME_DIR = $(SOURCE_DIR)/game
SOURCES_GAME = game free_game game_init 

TEXTURE_DIR = $(GAME_DIR)/textures
SOURCES_TEXTURE = set_textures print_image combine_image \
	combine_image_utils set_walls_coins_ennemies \
	set_textures_others set_textures_player \
	free_textures

HUD_DIR = $(GAME_DIR)/hud
SOURCES_HUD = hud hud_swords hud_health hud_utils

UPDATE_DIR = $(GAME_DIR)/update
SOURCES_UPDATE = update update_index

PLAYER_DIR = $(GAME_DIR)/player
SOURCES_PLAYER = player player_print player_utils

COLLECTIBLE_DIR = $(GAME_DIR)/collectible
SOURCES_COLLECTIBLE = collectibles collectible_print \
	collectible_print_move

SWORD_DIR = $(GAME_DIR)/sword
SOURCES_SWORD = sword_update sword_list sword_print \
	sword_utils

ENNEMY_DIR = $(GAME_DIR)/ennemy
SOURCES_ENNEMY = ennemy_list ennemy_update ennemy_print \
	ennemy_print_move

WINDOW_DIR = $(GAME_DIR)/window
SOURCES_WINDOW = init_window screen_array

SOURCES = $(addprefix $(SOURCE_DIR)/, $(addsuffix .c, $(SOURCES_MAIN))) \
	$(addprefix $(MAP_DIR)/, $(addsuffix .c, $(SOURCES_MAP))) \
	$(addprefix $(A_STAR_DIR)/, $(addsuffix .c, $(SOURCES_A_STAR))) \
	$(addprefix $(GAME_DIR)/, $(addsuffix .c, $(SOURCES_GAME))) \
	$(addprefix $(TEXTURE_DIR)/, $(addsuffix .c, $(SOURCES_TEXTURE))) \
	$(addprefix $(HUD_DIR)/, $(addsuffix .c, $(SOURCES_HUD))) \
	$(addprefix $(UPDATE_DIR)/, $(addsuffix .c, $(SOURCES_UPDATE))) \
	$(addprefix $(PLAYER_DIR)/, $(addsuffix .c, $(SOURCES_PLAYER))) \
	$(addprefix $(COLLECTIBLE_DIR)/, $(addsuffix .c, $(SOURCES_COLLECTIBLE))) \
	$(addprefix $(SWORD_DIR)/, $(addsuffix .c, $(SOURCES_SWORD))) \
	$(addprefix $(ENNEMY_DIR)/, $(addsuffix .c, $(SOURCES_ENNEMY))) \
	$(addprefix $(WINDOW_DIR)/, $(addsuffix .c, $(SOURCES_WINDOW)))

SOURCES_LIBFT = $(addprefix $(LIBFT_DIR)/source/, ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c)

OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.c=$(OBJECTS_DIR)/%.o)

INCLUDES = -I/usr/include -I./mlx -I./libft/include -I./include

MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm $(LIBFT_LIB)

DEP = $(OBJECTS:.o=.d)

FLUSH_STDOUT = 1> /dev/null
FLUSH_BOTH = > /dev/null 2>&1

all: $(MLX_LIB) $(LIBFT_LIB) $(OBJECTS_DIR) $(NAME)

norminette:
	clear
	norminette $(SOURCE_DIR) $(INCLUDE_DIR)

$(NAME): $(LIBFT_LIB) $(OBJECTS)
	@echo Linking $@ executable
	@$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES) $(OBJECTS) $(LIBS) 

$(MLX_LIB):
	@echo building mlx
	@make -C $(MLX_DIR) $(FLUSH_BOTH)

$(LIBFT_LIB): $(SOURCES_LIBFT)
	@echo building libft
	@make -C $(LIBFT_DIR) $(FLUSH_STDOUT)

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c
	@echo compiling $< into $@
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -g -c -o $@ $<

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)

clean:
	@rm -rf $(OBJECTS_DIR)
	@make clean -C $(LIBFT_DIR) $(FLUSH_STDOUT)
	@make clean -C $(MLX_DIR) $(FLUSH_STDOUT)

fclean: clean
	@rm -r $(NAME)
	@make fclean -C $(LIBFT_DIR) $(FLUSH_STDOUT)

re: fclean all

.PHONY: all clean fclean re norminette libft

-include $(DEP)
