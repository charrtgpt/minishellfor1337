#include "header.h"

t_token *new_token(char *value, enum e_token_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = value;
    token->type = type;
    token->next = NULL;
    return token;
}

t_token *tokenize_metachar(char **s)
{
    if (**s == '|')
        return ((*s)++, new_token(NULL, TOKEN_PIPE));
    else if (**s == '>' && (*s)[1] == '>')
        return ((*s)+=2, new_token(NULL, TOKEN_REDIR_APPEND));
    else if (**s == '>')
        return ((*s)++, new_token(NULL, TOKEN_REDIR_OUT));
    else if (**s == '<' && (*s)[1] == '<')
        return ((*s)+=2, new_token(NULL, TOKEN_HEREDOC));
    else if (**s == '<')
        return ((*s)++, new_token(NULL, TOKEN_REDIR_IN));
    
    return NULL;
}

char    *slice_string(char **input, int len)
{
    char *line = malloc(len + 1);
    if(!line)
        return NULL;
    ft_strncpy(line, *input, len);
    line[len] = '\0';
    *input += len;
    return line;
}

t_token *tokenize_word(char **input)
{
    int i = 0;
    char quote = '\0';           
    char *p = *input;           
    while (p[i])
    {
        if (quote)
        {
            if (p[i] == quote)
                quote = '\0';
        }
        else
        {
            if (p[i] == '\'' || p[i] == '"')
                quote = p[i]; 
            else if (ft_strchr(" |><", p[i]))
                break;           
        }
        i++;
    }

    if (i == 0)
        return NULL;

    return new_token(slice_string(input, i), TOKEN_WORD);
}
void add_token(t_token **head, t_token *new)
{
    if (!*head)
    {
        *head = new;
        return;
    }
    t_token *current = *head;
    while (current->next)
        current = current->next;
    current->next = new;
}

t_token   *tokenizer(char *input)
{
    t_token *head = NULL;
    t_token *new;
    while (*input)
    {
        while (ft_strchr(" \r\n", *input)) input++;  /*we are using ft_strchr as a character classifier
         to test if the current character (*input) is in a set of special characters.*/
        if (ft_strchr("|><", *input))
            new = tokenize_metachar(&input);
        else
            new = tokenize_word(&input);
        if (new) add_token(&head, new);
    }
    return head;
}