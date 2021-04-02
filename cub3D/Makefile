NAME = cub3D

CC = gcc

CFLAGS = -O3 -Wall -Wextra -Werror

MLX = minilibx_opengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRC = cub3d \
	parse \
	parse_map \
	parse_tools \
	parse_check \
	gnl \
	play \
	screen \
	screeen \
	sprite \
	bitmap \
	additional_tools

FIL = $(addsuffix .c, $(addprefix files/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(MAKE) -C ./minilibx_opengl
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ) $(B_OBJ)
	$(MAKE) -C ./minilibx_opengl/ clean
	rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	$(MAKE) -C ./minilibx_opengl/ clean
	@echo "\033[0m"

re: fclean all
