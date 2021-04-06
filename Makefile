NAME = minirt.a
CC=gcc
CFLAGS= -Wall -Wextra -Werror -lmlx -lXext -lX11 -lm
OBJ = ${SRCS:.c=.o}

SRCS =  gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		srcs/ft_atoi_rt.c \
		srcs/ft_function_maths.c \
		srcs/ft_image.c \
		srcs/ft_parsing.c \
		srcs/ft_parsing2.c \
		srcs/ft_parsing3.c \
		srcs/ft_parsing4.c \
		srcs/ft_intersection_cylinder.c \
		srcs/ft_rotation.c \
		srcs/ft_sphere.c\
		srcs/ft_triangle.c\
		srcs/ft_square_plan.c \
		srcs/ft_initialize.c\
		srcs/ft_function_maths_2.c \
		srcs/ft_function_maths_3.c \
		srcs/ft_ombre.c \
		srcs/ft_specular.c\
		srcs/ft_scale_color.c\
		srcs/ft_camera.c\
		srcs/ft_intensity_colors.c\
		srcs/ft_bitmap.c\
		srcs/ft_mirror.c\
		srcs/ft_clean.c\
		srcs/ft_utils.c\
		srcs/ft_key.c\
		

# COLORS
C_NO	=	"\033[00m"
C_OK	=	"\033[35m"
C_GOOD	=	"\033[32m"
C_ERROR	=	"\033[31m"
C_WARN	=	"\033[33m"

# DBG MESSAGE
SUCCESS	=	$(C_GOOD)SUCCESS$(C_NO)
OK		=	$(C_OK)OK$(C_NO)

all: $(NAME)

%.o: %.c
		@$(CC) -Iincludes $(CFLAGS)  -c $< -o $@
		@echo "Linking" [ $< ] $(OK)

$(NAME): $(OBJ)
	@make re -C libft/
	@make re -C minilibx-linux/
	@cp libft/libft.a ./$(NAME)
	@cp minilibx-linux/libmlx.a ./$(NAME)
	@ar rc $@ $^
	@echo "Compiling & indexing" [ $(NAME) ] $(SUCCESS)
	@$(CC) -Iincludes  $(OBJ) $(CFLAGS)  main.c  $(NAME) libft/libft.a minilibx-linux/libmlx.a  -o  minirt

test :
	@$(CC) -Iincludes  $(OBJ) $(CFLAGS)  main.c  $(NAME) libft/libft.a minilibx-linux/libmlx.a  -o  minirt

leak : 
	@$(CC) -Iincludes  $(OBJ) $(CFLAGS)  main.c  $(NAME) libft/libft.a minilibx-linux/libmlx.a -fsanitize=leak -fsanitize=address -fno-omit-frame-pointer -o  leak
clean:
	@make clean -C libft/
	@/bin/rm -f $(OBJ)
	@echo "[ft_printf] Removed object files!\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f leak
	@make fclean -C libft/
	@make clean -C minilibx-linux/
	@echo "Cleaning" [ $(NAME) ] $(OK)

re: fclean all test

.PHONY: all clean fclean re test