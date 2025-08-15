#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <fcntl.h>

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_REDIR_IN,      // <
    TOKEN_REDIR_OUT,     // >
    TOKEN_REDIR_APPEND,  // >>
    TOKEN_HEREDOC,       // <<
    TOKEN_PIPE           // |
}   t_token_type;

typedef struct s_token {
    char *value;
    struct s_token *next;
    t_token_type type;
} t_token;

typedef struct s_cmd {
    char **args;
    char *inp_file;
    char *out_file;
    char *heredoc;
    int app_over_mode; 
    struct s_cmd *next;
} t_cmd;

char        *user_input(void);
t_token     *tokenizer(char *input);
t_token_type get_metachar_type(char *s);
t_cmd       *parsing(t_token *tokens);
char    *ft_strdup(char *str);
char    *ft_strncpy(char *dest, const char *src, size_t l);
char *ft_strchr(char* s, char t);
void    expand_tokens(t_token *head);
int     heredoc(const char *delimiter);
void    execute_command(t_cmd *cmd);
int     ft_isalnum(int c);
size_t  ft_strlen(const char *str);
char    *ft_strcpy(char *dest, const char *src);
char    *ft_strcat(char *dest, const char *src);

#endif