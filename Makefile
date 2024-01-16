CC = cc
CFLAGS = -Wall -Werror -Wextra -g # -fsanitize=threads
NAME = philo
INC_FLAGS = -I ./inc/

SRC = 	src/main.c src/dinner.c src/init.c src/parse.c \
		src/debug.c src/utils.c src/time.c

$(NAME) : $(SRC)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean:
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re