NAME = test.out
SCR_DIR = src
SRCS = main.c
OBJS = ${SRCS:c=o}
C_FLAGS = -Werror -Wextra -Wall
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
INCLUDES = -I/usr/include -Imlx
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
GNL_DIR = gnl
GNL_LIB = $(GNL_DIR)/gnl.a
HEADER = include/so_long.h

all: $(MLX_LIB) $(GNL_LIB) $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(C_FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(GNL_LIB)

$(MLX_LIB):
	make --no-print-directory -C $(MLX_DIR)

$(GNL_LIB):
	@make --no-print-directory -C $(GNL_DIR)

%.o: $(SCR_DIR)/%.c
	@$(CC) $(C_FLAGS) -c -o $@ $< $(INCLUDES)

clean:
	@rm $(OBJS)
	@make clean --no-print-directory -C $(GNL_DIR)

fclean:
	@rm $(OBJS) $(NAME)
	@make fclean --no-print-directory -C $(GNL_DIR)

