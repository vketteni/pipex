NAME=pipex
CC=cc
FLAGS= -g -Wall -Wextra -Werror
SRSC = pipex.c \
	utils.c	\
	
OBJS = $(SRSC:.c=.o)

all: $(NAME)

${NAME}: ${OBJS} libft
	@${CC} ${FLAGS} ${OBJS} -Lsubmodules/libft -lft -o ${NAME}

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

libft:
	@${MAKE} -C submodules/libft 

clean:
	@${MAKE} clean -C submodules/libft
	rm -f $(OBJS)

fclean: clean
	@${MAKE} fclean -C submodules/libft
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re