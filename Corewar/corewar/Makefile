NAME =			corewar
INC =			-I./includes
LIB =			-lft -L ./libft
LIST =			args  ch_lst  err say flags  main  op read_bytes  pc cut_pc code read_exec op_add op_and op_ld op_lfork op_lld op_or op_sti op_xor op_aff op_fork op_ldi op_live op_lldi op_st op_sub op_zjmp
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
