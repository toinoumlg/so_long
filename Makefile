NAME := so_long

CC := cc
CFLAGS := -Wall -Wextra -Werror -std=gnu89 -g3

RM := rm -rf
MAKEFLAGS += --no-print-directory

OBJ_DIR := build
SRC_DIR := source
INC_DIR := include
LIBFT_DIR := libft
ASTAR_DIR := astar
BSP_DIR := bsp

LIBFT_INCLUDE := -I$(LIBFT_DIR)/$(INC_DIR)
ASTAR_INCLUDE := -I$(ASTAR_DIR)
BSP_INCLUDE := -I$(BSP_DIR)

LIBFT := $(LIBFT_DIR)/libft.a
ASTAR := $(ASTAR_DIR)/astar.a
BSP := $(BSP_DIR)/bsp.a
LIBS := $(ASTAR) $(LIBFT) $(BSP) -lm
INCLUDES = -I/usr/include $(LIBFT_INCLUDE) $(BSP_INCLUDE) $(ASTAR_INCLUDE) -I./include 

SRC_MAIN := main free_memory exit_error

SRC_MAP := \
	map/load_map \
	map/map_checker \
	map/rooms

SRC_GAME := \
	game/collectible \
	game/ennemy

SRCS := \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_MAIN))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_MAP))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_GAME))) \
	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_ENGINE))) \

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT)  $(ASTAR) $(BSP) $(OBJS)
	@echo "Linking $(NAME)"
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(LIBFT): FORCE
	@$(MAKE) -C $(LIBFT_DIR)

$(ASTAR): FORCE
	@$(MAKE) -C $(ASTAR_DIR)

$(BSP): FORCE
	@$(MAKE) -C $(BSP_DIR)

FORCE:

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -g -c -o $@ $<

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(ASTAR_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(ASTAR_DIR) fclean

re: fclean all

norm:
	norminette $(SRC_DIR) $(INC_DIR)

.PHONY: all clean fclean re norm FORCE

-include $(DEPS)
