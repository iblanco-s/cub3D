NAME	= cub3D

CC 		= gcc

CFLAGS	= -Wall -Wextra -Werror -g3 #-fsanitize=address

#Linux
MLX_FLAG = -Iinclude -ldl -lglfw -pthread -lm

#MAC
#MLX_FLAG = -framework Cocoa -framework OpenGL -framework IOKit -lglfw

RM		= rm -rf

SRC_DIR = src

OBJ_DIR	= obj

SRCS	= $(SRC_DIR)/parse/check.c \
		$(SRC_DIR)/parse/check_1.c \
		$(SRC_DIR)/parse/check_2.c \
		$(SRC_DIR)/parse/check_3.c \
		$(SRC_DIR)/parse/read_map.c \
		$(SRC_DIR)/parse/map_size1.c \
		$(SRC_DIR)/parse/map_size.c \
		$(SRC_DIR)/parse/texture_1.c \
		$(SRC_DIR)/parse/texture_2.c \
		$(SRC_DIR)/parse/parse.c \
		$(SRC_DIR)/raycasting/exec.c \
		$(SRC_DIR)/raycasting/exit.c \
		$(SRC_DIR)/raycasting/load_texture.c \
		$(SRC_DIR)/raycasting/move.c \
		$(SRC_DIR)/raycasting/raycasting_2.c \
		$(SRC_DIR)/raycasting/raycasting_3.c \
		$(SRC_DIR)/raycasting/raycasting_4.c \
		$(SRC_DIR)/raycasting/raycasting_5.c \
		$(SRC_DIR)/raycasting/minimap.c \
		$(SRC_DIR)/main.c \

OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT	= libft
LIBFT_A = $(LIBFT)/libft.a
LIBFT_INC = -I$(LIBFT)
LIBFT_OBJS = $(LIBFT)/*.o

MLX	= MLX42/include/MLX42
MLX_A = $(MLX)/libmlx42.a
MLX_INC = -I$(MLX)
MLX_OBJS = $(MLX)/*.o

#GLFW_INC = -I/opt/homebrew/include
#GLFW_LIB = -L/opt/homebrew/lib

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_A)
	@$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_A) $(MLX_FLAG) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(MLX_FLAG) $(LIBFT_INC) $(MLX_INC) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME) $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re