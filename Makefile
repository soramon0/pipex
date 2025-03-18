CC = cc
EXTRA_FLAGS= -g
CFLAGS = -Wall -Wextra -Werror $(EXTRA_FLAGS)
NAME = pipex
SRC = main.c $(shell find ./src -depth -maxdepth 1 -type f -name "*.c")
OBJ = $(SRC:.c=.o)
LIBFT_NAME = src/libft/libft.a

all: $(NAME)

libft: $(LIBFT_NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME)

$(LIBFT_NAME):
	$(MAKE) -C ./src/libft

clean:
	$(MAKE) -C src/libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C src/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
