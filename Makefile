# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 21:41:56 by rschleic          #+#    #+#              #
#    Updated: 2022/01/20 21:41:59 by rschleic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = fdf
SRC = 0_main.c 1_input.c 2_input_help.c 3_3dto2d.c 4_rendering.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))
OBJ_DIR = obj/
#obj is all the src files but with an .o
LIBFT = libft/libft.a
MINILIBX_DIR = minilibx_macos/
MINILIBX = $(MINILIBX_DIR)libmlx.a
MLX = -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MINILIBX_DIR = minilibx/
	MINILIBX = $(MINILIBX_DIR)libmlx.a
endif
#just for Linux

all : $(NAME)


$(OBJ_DIR)%.o : %.c
	@mkdir -p $$(dirname $@) > /dev/null
	@$(CC) $(FLAGS) -c $< -o $@ > /dev/null


$(NAME) : $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(FLAGS) $(OBJ) $(MLX) $(LIBFT) -o $(NAME)


$(LIBFT) :
	@make -sC libft > /dev/null


$(MINILIBX) :
	make -sC $(MINILIBX_DIR) > /dev/null
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