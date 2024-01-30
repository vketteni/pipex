NAME=pipex
CC=cc
CFLAGS=-Wall -Wextra -Werror

# Path: srcs
SRSC = source/pipex.c

OBJS = $(SRSC:.c=.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re