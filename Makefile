# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 16:36:46 by coder             #+#    #+#              #
#    Updated: 2022/01/18 22:42:18 by rschleic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = fdf
SRC = 0_main.c 1_input.c 2_input_help.c 3_3dto2d.c 4_rotations.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))
OBJ_DIR = obj/
#obj is all the src files but with an .o
LIBFT = libft/libft.a
MINILIBX_DIR = minilibx_macos/
MINILIBX = $(MINILIBX_DIR)libmlx.a
#GNL = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
MLX = -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
#MLX = -Lminilibx -lmlx -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz
#MLXTEST = -Lminilibx -lmlx -L/usr/lib -lXext
#OBJ = %.o
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MINILIBX_DIR = minilibx/
	MINILIBX = $(MINILIBX_DIR)libmlx.a
endif


all : $(NAME)

#$(NAME): $(OBJ)
#	$(CC) -Lminilibx -lminilibx -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz $(OBJ) -o $(NAME)

	
$(OBJ_DIR)%.o : %.c
	mkdir -p $$(dirname $@)
	$(CC) $(FLAGS) -c $< -o $@
	
#$(OBJ): %.c - 
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Iminilibx -O3 -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(FLAGS) $(OBJ) $(MLX) $(LIBFT) -o $(NAME)

$(LIBFT) : 
	make -C libft
	
$(MINILIBX) :
	make -sC $(MINILIBX_DIR)
#tries to make in the specified folder


clean : 
	make -C libft clean
	make -sC $(MINILIBX_DIR) clean
	$(RM) -rf $(OBJ_DIR)
	
fclean : clean
	make -C libft fclean
	$(RM) -f fdf

re : fclean all
	$(RM) -f fdf
	make all