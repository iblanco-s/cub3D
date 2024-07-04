NAME	= cub3D

CC 		= gcc

CFLAGS	= -Wall -Wextra -Werror -g3 #-fsanitize=address

MLX_FLAG = -lXext -lX11 -lm -lbsd

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
		$(SRC_DIR)/main.c \

OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT	= libft
LIBFT_A = $(LIBFT)/libft.a
LIBFT_INC = -I$(LIBFT)
LIBFT_OBJS = $(LIBFT)/*.o

MLX	= minilibx-linux
MLX_A = $(MLX)/libmlx.a
MLX_INC = -I$(MLX)
MLX_OBJS = $(MLX)/*.o

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_A) $(MLX_FLAG) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(MLX_FLAG) $(LIBFT_INC) $(MLX_INC) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT)
	@$(MAKE) clean -C $(MLX) 


fclean: clean
	$(RM) $(NAME) $(LIBFT_A) $(MLX_A)

re: fclean all

.PHONY: all clean fclean re