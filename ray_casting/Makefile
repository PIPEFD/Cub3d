NAME        =   cub3d
LIBFT     	=	libft/libft.a
INC         =   inc/
SRC_DIR     =   src/
MLX         =   build/libmlx42.a

CC          =   gcc -fsanitize=address -g3
FLAGS       =   -Wall -Wextra -Werror
RM          =   rm -f

SRC_FILES   =   cub3d.c


SRC =   $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		= objs/
OBJS_FILES	= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)



# COLORS

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;31m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
CLEAR = \033[0m\n
OKLOGO = \033[80G\033[32m[OK]\033[0m\n


# **************************************************************************** #

all:        $(NAME)

$(NAME):    $(LIBFT) $(MLX) $(OBJS_FILES)
			@printf "$(BLUE)COMPILING... $< $(DEF_COLOR)$(CLEAR)"
			@$(CC) -o $(NAME) $(FLAGS) $(OBJS_FILES) $(LIBFT) $(MLX) -I$(INCLUDES) -ldl -lglfw -pthread -lm
			@printf "033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"
			@echo "$(GREEN)CUB3D COMPILED SUCCESFUL!$(DEF_COLOR)"

$(LIBFT):
			@make -C ./libft
$(MLX):
			@cmake -B build ./mlx 2>/dev/null
			@make ./build 2>/dev/null

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

.c.o:
			@printf "$(BLUE)COMPILING... $< $(DEF_COLOR)"
			@$(CC) $(FLAGS) -I$(INC) -c $< -o $(<:.c=.o)

clean:
			@$(RM) $(OBJ)
			@echo "$(YELLOW)FILES REMOVED!$(DEF_COLOR)"
			make clean -C ./libft
#@cmake clean -C ./build

fclean:     clean
			@make fclean -C ./libft
			@$(RM)  $(NAME)
			@echo "$(RED)REMOVED ALL FILES!$(DEF_COLOR)"


re:         fclean all

.PHONY:     all clean fclean re libft print