#include "header.h"

static int is_var_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

char *expand_variable_in_str(const char *str)
{
    int i = 0;
    char *result = ft_strdup("");
    if (!result)
        return NULL;

    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && is_var_char(str[i + 1]))
        {
            i++;
            int start = i;
            while (str[i] && is_var_char(str[i]))
                i++;
            int len = i - start;
            char *var_name = malloc(len + 1);
            if (!var_name)
            {
                free(result);
                return NULL;
            }
            ft_strncpy(var_name, &str[start], len);
            var_name[len] = '\0';

            char *value = getenv(var_name);
            free(var_name);
            if (!value)
                value = "";

            char *tmp = result;
            result = malloc(ft_strlen(tmp) + ft_strlen(value) + 1);
            if (!result)
            {
                free(tmp);
                return NULL;
            }
            ft_strcpy(result, tmp);    
            ft_strcat(result, value); 
            free(tmp);
        }
        else
        {
            int len = ft_strlen(result); 
            char *tmp = result;
            result = malloc(len + 2);
            if (!result)
            {
                free(tmp);
                return NULL;
            }
            ft_strcpy(result, tmp);
            result[len] = str[i];
            result[len + 1] = '\0';
            free(tmp);
            i++;
        }
    }
    return result;
}

void expand_tokens(t_token *head)
{
    t_token *temp = head;
    while (temp)
    {
        if (temp->type == TOKEN_WORD && temp->value)
        {
            char *expanded = expand_variable_in_str(temp->value);
            if (expanded)
            {
                free(temp->value);
                temp->value = expanded;
            }
        }
        temp = temp->next;
    }
}