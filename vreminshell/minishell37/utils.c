#include "header.h"

t_token_type get_metachar_type(char *s)
{
    if (!s)
        return TOKEN_WORD;
    if (!strcmp(s, "|"))
        return TOKEN_PIPE;
    if (!strcmp(s, "||"))
        return -1; //To handle
    if (!strcmp(s, ">"))
        return TOKEN_REDIR_OUT;
    if (!strcmp(s, ">>"))
        return TOKEN_REDIR_APPEND;
    if (!strcmp(s, "<"))
        return TOKEN_REDIR_IN;
    if (!strcmp(s, "<<"))
        return TOKEN_HEREDOC;
    return TOKEN_WORD;
}