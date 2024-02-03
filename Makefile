NAME=pipex
CC=cc
CFLAGS=-Wall -Wextra -Werror

# Path: srcs
SRSC = pipex.c \
	utils.c	\

OBJS = $(SRSC:.c=.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

${NAME}: ${OBJS}
	@${MAKE} -C submodules/libft bonus
	@${CC} ${FLAGS} ${OBJS} -Lsubmodules/libft -lft -o ${NAME}

clean:
	@${MAKE} clean -C submodules/libft
	rm -f $(OBJS)

fclean: clean
	@${MAKE} fclean -C submodules/libft
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re