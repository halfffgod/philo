NAME = philo

FLAGS = -Wall -Wextra -Werror

SRC =	main.c utils.c init.c errors.c living.c time_utils.c death.c

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