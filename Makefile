MLX_DIR = minilibx_opengl_20191021
PRINTF_DIR = ft_printf

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror \
           -I$(MLX_DIR) \
           -I$(PRINTF_DIR)

LIBRARIES = -L$(MLX_DIR) -L$(PRINTF_DIR) -lmlx -lftprintf -framework OpenGL -framework AppKit

NAME = fractol
SRC_FILES = mandelbrot.c moves.c drawset.c julia.c burningship.c helper_functions.c main.c ft_atof.c
OBJ = $(SRC_FILES:.c=.o)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	make -C $(PRINTF_DIR)
	$(CC) $(CC_FLAGS) $(OBJ) -o $(NAME) $(LIBRARIES)

all: $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(MLX_DIR) clean
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(MLX_DIR) clean
	make -C $(PRINTF_DIR) clean

re: fclean $(NAME)

.PHONY: all clean fclean re