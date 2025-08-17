NAME = minishell

SRC_FILS =  call.c helperf.c main.c redirection.c tools.c ft_split.c \
			lbtools.c more_tools.c fring_tools.c handle_pipe.c numbrtool.c \
			envir.c list_to_arr.c echho.c builtinss.c excutcmd.c handlerss.c \
			ft_cd.c ft_pwd.c exporthelper.c ft_export.c ft_isalnum.c ft_isalpha.c\
			ft_unset.c ft_env.c ft_exit.c heredoc.c pipe_tool.c excut_tool.c\
			exit_helper.c

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
