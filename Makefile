# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 16:36:46 by coder             #+#    #+#              #
#    Updated: 2022/01/16 12:58:47 by rschleic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror -pg -g
MEM = -fsanitize=address -g 
NAME = fdf
SRC = 0_main.c 1_input.c 2_input_help.c 3_3dto2d.c 4_rotations.c
LIBFT = libft/libft.a
GNL = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
MLX = -Lminilibx -lmlx -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz
#MLXTEST = -Lminilibx -lmlx -L/usr/lib -lXext
#OBJ = %.o

all : win $(NAME)

#$(NAME): $(OBJ)
#	$(CC) -Lminilibx -lminilibx -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz $(OBJ) -o $(NAME)

#$(OBJ): %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Iminilibx -O3 -c $< -o $@

$(NAME) : $(SRC) $(LIBFT)
	$(CC) $(FLAGS) $(MEM) $(SRC) $(MLX) $(LIBFT) $(GNL) -o $(NAME)

$(LIBFT) : 
	make -C libft

win :
	export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0

clean : 
	make -C libft clean
fclean : 
	make -C libft fclean
	rm -f fdf

re : fclean all
	rm -f fdf
	make all