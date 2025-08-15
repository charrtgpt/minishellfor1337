#include "header.h"

const char *token_type_str(t_token_type type)
{
    if (type == TOKEN_WORD)
        return "WORD";
    if (type == TOKEN_REDIR_IN)
        return "REDIR_IN";
    if (type == TOKEN_REDIR_OUT)
        return "REDIR_OUT";
    if (type == TOKEN_REDIR_APPEND)
        return "REDIR_APPEND";
    if (type == TOKEN_HEREDOC)
        return "HEREDOC";
    if (type == TOKEN_PIPE)
        return "PIPE";
    return "UNKNOWN";
}

void print_tokens(t_token *head)
{
    if (head == NULL)
    {
        printf("No tokens.\n");
        return;
    }
    t_token *current = head;
    while (current)
    {
        printf("%s,%s\n", current->value, token_type_str(current->type));
        current = current->next;
    }
}

void print_commands(t_cmd *head)
{
    if (head == NULL)
    {
        printf("No commands\n");
        return;
    }
    t_cmd *current = head;
    while (current)
    {
        printf("Command:\n");
        if (current->args)
        {
            int i = 0;
            while (current->args[i])
            {
                printf("  Arg %d: %s\n", i, current->args[i]);
                i++;
            }
        }
        if (current->inp_file)
            printf("  Input File: %s\n", current->inp_file);
        if (current->out_file)
            printf("  Output File: %s\n", current->out_file);
        if (current->heredoc)
            printf("  Heredoc: %s\n", current->heredoc);
        current = current->next;
    }
}
int main()
{
    char *input;
    t_token *tokens;
    t_cmd *commands;

    while (1)
    {
        input = user_input();
        tokens = tokenizer(input);
        expand_tokens(tokens);
        print_tokens(tokens);
        commands = parsing(tokens);
        print_commands(commands);
        t_cmd *tmp = commands;
        while (tmp)
        {
            execute_command(tmp);
            tmp = tmp->next;
        }
        printf("mission completed!\n");
        free(input);
    }
}
