NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build
INC_FLAGS = -I $(INC_DIR)

SRC_FILES = main.c \
			parse.c \
			init.c \
			dinner.c \
			forks.c \
			cleanup.c \
			time.c \
			utils.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

$(NAME) : $(OBJS)
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(INC_FLAGS)
	@echo "Done!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re