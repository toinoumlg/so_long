NAME = libft.a
CFLAGS = -Werror -Wall -Wextra -MMD -MP -g -c
CC = cc
AR = ar rcs
INCLUDE = -I./include

SRC_DIR = source
OBJ_DIR = build

SRC_FILES = strlen strlcpy strlcat memcmp atoi \
		strncmp toupper tolower isprint isdigit \
		isascii isalpha isalnum substr strchr \
		strrchr strnstr strjoin strtrim split \
		strdup itoa strmapi memset memchr memcpy \
		bzero memmove calloc putchar_fd putstr_fd \
		putendl_fd putnbr_fd striteri \
		lstnew lstadd_front lstsize \
		lstlast lstadd_back lstdelone \
		lstclear lstiter lstmap get_next_line

SRC = $(addprefix $(SRC_DIR)/ft_, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo creating library: $@
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo compiling $< into $@
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo deleting $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo deleting $(NAME)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)