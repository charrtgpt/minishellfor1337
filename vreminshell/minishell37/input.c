#include "header.h"

char    *user_input()
{
    char *input;
    while(1)
    {
        input = readline("My_Minishell> ");
        if(!input)
        {
            printf("Exit!\n");
            exit(0);
        }
        if(*input == '\0')
        {
            free(input);
            continue;
        }
        add_history(input);
        return input;
    }
}