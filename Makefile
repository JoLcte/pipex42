# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/15 23:17:06 by jlecomte          #+#    #+#              #
#    Updated: 2021/09/30 20:38:27 by jlecomte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = clang -Wall -Wextra -Werror
LIBFLAGS = -L ./libft -lft

HEADER = includes

SRC_DIR = src
SRC_DIR_BONUS = src_bonus
OBJ_DIR = obj

SRC_F = path_parse.c \
       	pipex.c \
		utils.c \
		main.c
SRC_F_BONUS = path_parse_bonus.c \
	      pipex_bonus.c \
	      utils_bonus.c \
	      main_bonus.c

ifdef	WITH_BONUS
	CFLAGS += -D BONUS=1
	SRC_DIR = $(SRC_DIR_BONUS)
	SRC_F = $(SRC_F_BONUS)
endif

SRC = $(addprefix $(SRC_DIR)/, $(SRC_F))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_F:%.c=%.o))


all: $(NAME)


$(NAME) : $(OBJ)
	@echo "\e[38;5;38m *** Compiling Libft Library ***"
	@make -C libft
	@$(CFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)
	@echo "\e[38;5;38m- Pipex Compilation Completed -"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CFLAGS) -I libft/includes -I $(HEADER) -c $< -o $@
	@echo "\e[38;5;104mCreating: $(@:%=%)\e[m"

clean:
	@if [ -d libft/obj ]; then rm -rf libft/obj && echo "\e[38;5;125mRemoving Libft Object Files"; else echo "make: No libft objects to remove."; fi;
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR) && echo "\e[38;5;125mRemoving Object Files"; else echo "make: No $(NAME) objects to remove."; fi;

fclean: clean
	@if [ -f libft/libft.a ]; then rm -f libft/libft.a && echo "\e[38;5;161mRemoving - Libft Library -\e[m"; else echo "make: No libft to remove."; fi;
	@if [ -f $(NAME) ]; then rm -f $(NAME) && echo "\e[38;5;161mRemoving - $(NAME) -"; else echo "make: No binary $(NAME) to remove."; fi;

bonus:	
	@$(MAKE) WITH_BONUS=1


re: fclean all

.PHONY: all bonus clean fclean re
