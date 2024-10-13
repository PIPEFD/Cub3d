NAME        =   cub3d
LIBFT       =   libft/libft.a
INC         =   inc/
SRC_DIR     =   src/
MLX         =   build/libmlx42.a

CC          =   gcc
FLAGS       =   -Wall -Wextra -Werror -g3 #-fsanitize=address
RM          =   rm -f

SRC_FILES   =   main.c \
				hook.c \
				init_data.c \
				init_setup.c \
				player_setup.c \
				rays_horizontal.c \
				rays_vertical.c \
				draw.c \
				map_utils.c \
				rays_setup.c \
				utils_math.c \
				render_2d.c \
				render_3d.c


SRC         =   $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR     =   objs/
OBJS_FILES  =   $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# COLORS
DEF_COLOR   =   \033[0;39m
BLUE        =   \033[0;94m
GREEN       =   \033[0;92m
RED         =   \033[0;31m
YELLOW      =   \033[0;93m
CLEAR       =   \033[0m\n

all:        $(NAME)

$(NAME):    $(LIBFT) $(MLX) $(OBJS_FILES)
			@printf "$(BLUE)COMPILING... $(DEF_COLOR)$(CLEAR)"
			@$(CC) $(FLAGS) -o $(NAME) $(OBJS_FILES) $(LIBFT) $(MLX) -ldl -lglfw -pthread -lm
			@echo "$(GREEN)CUB3D COMPILED SUCCESSFULLY!$(DEF_COLOR)"

$(LIBFT):
			@make -C ./libft

$(MLX):
			@cmake -B build ./MLX42 2>/dev/null
			@make -C build 2>/dev/null
			cmake -DBUILD_TESTS=ON -B build && cmake --build build --parallel

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(FLAGS) -I$(INC) -c $< -o $@

clean:
			@$(RM) $(OBJS_FILES)
			@echo "$(YELLOW)OBJECT FILES REMOVED!$(DEF_COLOR)"
			@make clean -C ./libft
			@make clean -C build
normi:
			norminette ./src
			norminette ./inc
fclean:     clean
			@make fclean -C ./libft
			@$(RM)  $(NAME)
			@echo "$(RED)ALL FILES REMOVED!$(DEF_COLOR)"

re:         fclean all

.PHONY:     all clean fclean re
