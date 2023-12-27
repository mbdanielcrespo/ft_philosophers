CC = CC
CFLAGS = -Wall -Werror -Wextra -g3 # -fsanitize=address
NAME = philo
INC_FLAGS = -I ./inc/

SRC = src/main.c

$(NAME) : $(SRC)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean:
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re