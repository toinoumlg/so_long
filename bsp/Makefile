LIB := bsp.a

AR := ar rcs
CC = cc
CFLAGS = -Werror -Wextra -Wall -g3

SOURCE_DIR := source/
OBJECTS_DIR := build/
INCLUDE_DIR := include/
LIBFT_DIR := ../libft

C_FILES = bsp
H_FILES = bsp_struct

SOURCES = $(addprefix $(SOURCE_DIR), $(addsuffix .c, $(C_FILES)))
OBJECTS = $(patsubst $(SOURCE_DIR)%.c,$(OBJECTS_DIR)%.o,$(SOURCES))
HEADERS = $(addprefix $(INCLUDE_DIR), $(addsuffix .h, $(H_FILES)))
LIBFT := $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)/include -I./include

all: $(LIBFT) $(LIB)

$(LIB): $(OBJECTS)
	$(AR) $(LIB) $(OBJECTS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJECTS_DIR)%.o: $(SOURCE_DIR)%.c $(HEADERS) | $(OBJECTS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)

clean:
	rm -rf $(OBJECTS_DIR)


fclean: clean
	rm -f $(LIB)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
