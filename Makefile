NAME = a.out
SRC_DIR = src
SRCS = main.c map_init.c map_checker.c free_memory.c \
	utils.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = $(SRC_DIR)/obj
C_FLAGS = -Werror -Wextra -Wall
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
INCLUDE_DIR = include
INCLUDES = -I/usr/include -Imlx -Ilibft/include
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
HEADER = include/so_long.h
LIBFTPRINTF_LIB = $(LIBFTPRINTF_DIR)/libftprintf.a
LIBFTPRINTF_DIR = libftprintf
CHECK_SYSTEM = config.txt

all: $(CHECK_SYSTEM) $(MLX_LIB) $(LIBFTPRINTF_LIB) $(NAME)

norminette:
	norminette $(SRC_DIR) $(INCLUDE_DIR)

$(NAME): $(OBJS) $(LIBFTPRINTF_LIB) $(HEADER) $(MLX_LIB)
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

clean:
	@rm -fr $(OBJ_DIR) $(CHECK_SYSTEM)
	@make clean --no-print-directory -C $(LIBFTPRINTF_DIR)

fclean:
	@rm -fr $(OBJ_DIR) $(NAME) $(CHECK_SYSTEM)
	@make fclean --no-print-directory -C $(LIBFTPRINTF_DIR)

