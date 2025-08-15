#include "header.h"

t_cmd *new_command()
{
    t_cmd *command = malloc(sizeof(t_cmd));
    if (!command)
        return NULL;
    command->args = NULL;
    command->inp_file = NULL;
    command->out_file = NULL;
    command->heredoc = NULL;
    command->app_over_mode = 0;
    command->next = NULL;

    return command;
}

t_cmd *parsing(t_token *tokens)
{
    t_cmd *head = NULL;
    t_cmd *current_cmd = NULL;
    t_token *current_token = tokens;

    if (!tokens)
        return NULL;

    while (current_token)
    {
        if (!current_cmd)
        {
            current_cmd = new_command();
            if (!current_cmd)
                return NULL;
            if (!head)
                head = current_cmd;
        }

        if (current_token->type == TOKEN_PIPE)
        {
            current_cmd->next = new_command();
            current_cmd = current_cmd->next;
            if (!current_cmd)
                return NULL;
            current_token = current_token->next;
        }
        else if (current_token->type == TOKEN_HEREDOC)
        {
            current_token = current_token->next;
            if (current_token)
            {
                free(current_cmd->heredoc);
                current_cmd->heredoc = ft_strdup(current_token->value);
                current_token = current_token->next;
            }
            else
            {
                printf("Expected heredoc delimiter\n");
                return NULL;
            }
        }
        else if (current_token->type == TOKEN_REDIR_IN)
        {
            current_token = current_token->next;
            if (current_token)
            {
                free(current_cmd->inp_file);
                current_cmd->inp_file = ft_strdup(current_token->value);
                current_token = current_token->next;
            }
            else
            {
                printf("Expected input file after '<'\n");
                return NULL;
            }
        }
        else if (current_token->type == TOKEN_REDIR_OUT || current_token->type == TOKEN_REDIR_APPEND)
        {
            if(current_token->type == TOKEN_REDIR_APPEND)
                current_cmd->app_over_mode = 1;
            else
                current_cmd->app_over_mode = 0;
            current_token = current_token->next;
            if (current_token)
            {
                free(current_cmd->out_file);
                current_cmd->out_file = ft_strdup(current_token->value);
                current_token = current_token->next;
            }
            else
            {
                printf("Expected output file after redirection\n");
                return NULL;
            }
        }
        else if (current_token->type == TOKEN_WORD)
        {
            int arg_count = 0;
            char **new_args;

            if (current_cmd->args)
            {
                while (current_cmd->args[arg_count])
                    arg_count++;
            }

            new_args = malloc(sizeof(char *) * (arg_count + 2));
            if (!new_args)
                return NULL;
            int i = 0;
            while (i < arg_count)
            {
                new_args[i] = current_cmd->args[i];
                i++;
            }

            free(current_cmd->args);

            new_args[arg_count] = ft_strdup(current_token->value);
            if (!new_args[arg_count])
            {
                free(new_args);
                return NULL;
            }
            new_args[arg_count + 1] = NULL;

            current_cmd->args = new_args;
            current_token = current_token->next;
        }
        else
        {
            current_token = current_token->next;
        }
    }
    return head;
}

void free_command(t_cmd *head)
{
    t_cmd *current = head;
    t_cmd *next;

    while (current)
    {
        next = current->next;
        if (current->args)
        {
            int i = 0;
            while (current->args[i])
            {
                free(current->args[i]);
                i++;
            }
            free(current->args);
        }
        if (current->inp_file)
            free(current->inp_file);
        if (current->out_file)
            free(current->out_file);
        if (current->heredoc)
            free(current->heredoc);

        free(current);
        current = next;
    }
}