# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlam <tlam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 14:33:17 by tlam              #+#    #+#              #
#    Updated: 2024/03/19 14:33:18 by tlam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
OUT_DIR = ./obj
SRC = $(addprefix src/, main.c \
						philosophers.c \
						philo_routine.c \
						monitor.c \
						errors.c \
						utils.c \
)

OBJS := $(SRC:src/%.c=$(OUT_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -Iincludes -Ilibft/includes
LFT = libft/libft.a

all: libft $(NAME)

libft:
	@make -C libft/

$(NAME): $(OBJS) $(LFT)
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME)

$(OUT_DIR)/%.o: src/%.c
	@printf "\033[0;33mGenerating philo objects... %-33.33s\r" $@
	@mkdir -p $(OUT_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/

re: fclean all

valgrind : all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all libft clean fclean re