# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 11:09:44 by mdonchen          #+#    #+#              #
#    Updated: 2019/04/30 11:26:05 by mdonchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mdonchen.filler

FLAGS = -Wall -Werror -Wextra -g -Iincludes/

SRC = src/ft_abs.c src/main.c src/read_input.c src/readmap.c src/utils.c

OBJ = $(SRC:%.c=%.o) 

all: $(NAME)

%.o:%.c
	@gcc -c $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	@gcc $(OBJ) -o $(NAME)

clean: 
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
