# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 17:58:56 by jlecomte          #+#    #+#              #
#    Updated: 2021/09/30 23:53:52 by jlecomte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CCF = clang -Wall -Wextra -Werror

OBJ_DIR = obj
SRC_DIR = src

SRC_F = add_on_pipex.c \
	ft_split_pipex.c \
	ft_strchr.c \
	ft_strjoin.c \
	ft_strncmp.c \
	ft_strlcpy.c \
	ft_strlen.c \
        ft_strtrim.c \
	gnl.c \
	gnl_utils.c

SRC = $(addprefix $(SRC_DIR)/,$(SRC_F))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_F:%.c=%.o))

HEADER = includes

all:	$(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@echo "\033[44m- Libft Compilation Completed -\033[m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CCF) -I $(HEADER) -c $< -o $@
	@echo "\033[0;36mCreating: $(@:%=%)\033[m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;35mRemoving $(NAME) Object Files\033[m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[45mRemoving - $(NAME) -\033[m"

re: fclean all

.PHONY: all clean fclean re
