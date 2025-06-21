# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 14:53:49 by hporta-c          #+#    #+#              #
#    Updated: 2025/06/21 09:17:19 by hporta-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
MLX_DIR = minilibx-linux
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR)
MLX = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS = get_next_line.c get_next_line_utils.c ft_split.c main.c \
		fill_map.c project_map.c draw.c event_litsener.c \
		colors.c utils.c utils_others.c mlx_utils.c clean_up.c \
		fill_utils.c trans_scale.c
OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean all re