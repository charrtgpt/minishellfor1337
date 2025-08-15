CC = gcc

NAME = minishell

SRCS = libft.c main.c input.c tokenizing.c parser.c utils.c expand.c exec.c

OBJS = $(SRCS:.c=.o)

LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re