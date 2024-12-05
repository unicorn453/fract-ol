CC_FLAGS = -Wall -Wextra -Werror -I/Users/kruseva/Desktop/AllProjects/fract-ol/minilibx_opengl_20191021

NAME = fractol

SRC_FILES = mandelbrot.c moves.c drawSet.c julia.c burningship.c

LIBRARIES = -L/Users/kruseva/Desktop/AllProjects/fract-ol/minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit

OBJ = $(SRC_FILES:.c=.o)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C /Users/kruseva/Desktop/AllProjects/fract-ol/minilibx_opengl_20191021
	$(CC) $(CC_FLAGS) $(OBJ) -o $(NAME) $(LIBRARIES)

clean:
	rm -f $(OBJ)
	make -C /Users/kruseva/Desktop/AllProjects/fract-ol/minilibx_opengl_20191021 clean

fclean: clean
	rm -f $(NAME)
	make -C /Users/kruseva/Desktop/AllProjects/fract-ol/minilibx_opengl_20191021 clean

re: fclean $(NAME)