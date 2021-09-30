# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/15 23:17:06 by jlecomte          #+#    #+#              #
#    Updated: 2021/09/30 23:52:13 by jlecomte         ###   ########.fr        #
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
	@echo "\033[44m *** Compiling Libft Library ***\033[m"
	@make -C libft
	@$(CFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)
	@echo "\033[44m- Pipex Compilation Completed -\033[m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CFLAGS) -I libft/includes -I $(HEADER) -c $< -o $@
	@echo "\033[0;36mCreating: $(@:%=%)\033[m"

clean:
	@if [ -d libft/obj ]; then rm -rf libft/obj && echo "\033[0;35mRemoving: Libft Object Files\033[m"; else echo "make: No libft objects to remove."; fi;
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR) && echo "\033[0;35mRemoving: $(NAME) Object Files\033[m"; else echo "make: No $(NAME) objects to remove."; fi;

fclean: clean
	@if [ -f libft/libft.a ]; then rm -f libft/libft.a && echo "\033[45mRemoving - Libft Library -\033[m"; else echo "make: No libft to remove."; fi;
	@if [ -f $(NAME) ]; then rm -f $(NAME) && echo "\033[45mRemoving - $(NAME) -\033[m"; else echo "make: No binary $(NAME) to remove."; fi;

bonus:	
	@$(MAKE) WITH_BONUS=1


re: fclean all

.PHONY: all bonus clean fclean re
