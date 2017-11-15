make -C libft/ fclean && make -C libft/
gcc -Wall -Wextra -Werror get_next_line.c get_next_line.h main_test.c libft/libft.a -g -fsanitize=address 
