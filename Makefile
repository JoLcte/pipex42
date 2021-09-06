# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/15 23:17:06 by jlecomte          #+#    #+#              #
#    Updated: 2021/08/27 15:11:22 by jlecomte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = clang -Wall -Wextra -Werror
LIBFLAGS = -L ./libft -lft


OBJ_DIR = obj
SRC_DIR = src

SRC_F = parsing.c\
	pipex.c\
	main.c

SRC = $(addprefix $(SRC_DIR)/,$(SRC_F))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_F:%.c=%.o))

HEADER = includes

all: $(NAME)


$(NAME) : $(OBJ)
	@echo "\e[38;5;38m *** Creating Libft Library ***"
	@make -C libft
	@$(CFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)
	@echo "\e[38;5;38m- Pipex Compilation Complete -"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CFLAGS) -I libft/includes -I $(HEADER) -O3 -c $< -o $@
	@echo "\e[38;5;104mCreated: $(@:%=%)"
clean:
	@rm -rf libft/*.o
	@echo "\e[38;5;125mRemoved Libft Object Files"
	@rm -rf $(OBJ_DIR)
	@echo "\e[38;5;125mRemoved Object Files"

fclean: clean
	@rm -f libft/libft.a
	@echo "\e[38;5;161mRemoved - Libft Library -\e[m"
	@rm -f $(NAME)
	@echo "\e[38;5;161mRemoved - $(NAME) -"

bonus: CCF += -D BONUS)
bonus: all

re: fclean all

.PHONY: all bonus clean fclean re
