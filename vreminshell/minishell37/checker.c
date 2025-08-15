#include "header.h"

int check(t_token *tokens)
{
    if (!tokens)
        return 1;

    t_token *curr = tokens;

    if (curr->type == TOKEN_PIPE)
    {
        printf("Unexpected: '|'\n");
        return 0;
    }
    while (curr)
    {
        if (curr->type != TOKEN_WORD)
        {
            if (!curr->next || curr->next->type != TOKEN_WORD)
            {
                if(curr->next)
                    printf("Unexpected token: %s \n", curr->next->value);
                else
                    printf("Unexpected token \n");
                return 0;
            }
        }
        curr = curr->next;
    }
    return 1;
}