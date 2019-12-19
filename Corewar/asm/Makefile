NAME =			asm
INC =			-I./includes
LIB =			-lft -L ./libft
LIST =			main terminates	gnl_asm read_file content read_contents tools pc_info read_code read_code_utils read_arg terminates2 mlabel label
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
