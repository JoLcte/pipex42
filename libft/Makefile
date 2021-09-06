# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 17:58:56 by jlecomte          #+#    #+#              #
#    Updated: 2021/08/26 23:35:27 by jlecomte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CCF = clang -Wall -Wextra -Werror

OBJ_DIR = obj
SRC_DIR = src

SRC_F = add_on_pipex.c \
	ft_split_pipex.c \
	ft_strchr.c \
        ft_strtrim.c	

SRC = $(addprefix $(SRC_DIR)/,$(SRC_F))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_F:%.c=%.o))

HEADER = includes

all:	$(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@echo "\e[38;5;38m- Libft Compilation Complete -"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CCF) -I $(HEADER) -O3 -c $< -o $@
	@echo "\e[38;5;104mCreated: $(@:%=%)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\e[38;5;125mRemoved Object Files"

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
