# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/26 20:56:24 by mdonchen          #+#    #+#              #
#    Updated: 2019/07/26 20:56:26 by mdonchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME =			lem-in
INC =			-I./includes
LIB =			-lft -L ./libft
LIST =			error gnl main read_validate rooms node utils link paths \
			   	b_f_s ants send_ants
OBJ =			$(addprefix obj/, $(addsuffix .o, $(LIST)))

all: $(NAME)

obj/%.o: src/%.c
	@gcc -c $< -o $@ $(INC)

$(NAME): obj $(OBJ)
	@make -C libft
	@gcc $(OBJ) -o $(NAME) $(LIB)

obj:
	@mkdir obj

clean:
	@make -C libft clean
	@rm -rf obj
	
fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all
