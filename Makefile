# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 21:41:56 by rschleic          #+#    #+#              #
#    Updated: 2022/01/23 20:02:02 by rschleic         ###   ########.fr        #
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

UNAME = $(shell uname)
ifeq ($(UNAME),Linux)
	MINILIBX_DIR = minilibx/
	MLX = -Lminilibx -lmlx -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz
endif

all : $(NAME)


$(OBJ_DIR)%.o : %.c
#if that obj_dir%.o file does not exist -> execute the code
#compares the .o file creation blabla with the .c file creation
#recompiles only after .c files time changed %.o : %.c
	@echo $@ $<
	@mkdir -p $$(dirname $@) > /dev/null
#the $@ is like a Variable and gets replaced by the lhs\
#-p makes parent directories
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