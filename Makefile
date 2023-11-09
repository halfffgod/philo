NAME = philo
FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
SRC =	main.c utils.c init.c errors.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	@gcc $(FLAGS) -c $< -o $@
$(NAME) : $(OBJ)
	@gcc $(FLAGS) $(OBJ) -o $(NAME)

clean : 
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : re fclean clean all