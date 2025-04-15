# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 20:36:01 by jgomez-d          #+#    #+#              #
#    Updated: 2025/04/12 21:56:06 by jgomez-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = pipex
CFLAGS  = -Wall -Wextra -Werror -g 
#-fsanitize=address,leak
CHEKER    = checker
LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a
SRC     = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(LIB_NAME) $(NAME)

$(LIB_NAME):
	@make -C $(LIB_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

clean:
	@rm -f $(OBJ) 
	@make -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME) $(CHEKER)
	@make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re