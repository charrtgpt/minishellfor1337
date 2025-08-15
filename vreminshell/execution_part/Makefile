NAME = minishell

SRC_FILS = call.c helperf.c main.c redirection.c tools.c ft_split.c \
			lbtools.c more_tools.c fring_tools.c handle_pipe.c numbrtool.c \
			envir.c list_to_arr.c

FLAGS = -Wall -Wextra -Werror

OBJ_FILS = $(SRC_FILS:.c=.o)

$(NAME): $(OBJ_FILS)
		cc $(FLAGS) $(OBJ_FILS) -lreadline -o $(NAME)

all: $(NAME)

%.o: %.c
		cc $(FLAGS) -c $< -o $@

clean:
		rm -f $(OBJ_FILS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re

.SECONDARY:
