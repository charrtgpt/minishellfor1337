#include "header.h"

char *ft_strdup(char *str)
{
    int i = 0;
    int l = 0;
    char *string_cpy;

    if (!str)
        return NULL;
    while (str[l])
        l++;
    string_cpy = malloc(sizeof(char) * (l + 1));
    if (string_cpy != NULL)
    {
        while (str[i])
        {
            string_cpy[i] = str[i];
            i++;
        }
        string_cpy[i] = '\0';
    }
    return string_cpy;
}

char *ft_strncpy(char *dest, const char *src, size_t l) {
    size_t i = 0;
    while (l > i && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    while (i < l)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

char *ft_strchr(char* s, char t)
{
    while (*s)
    {
        if (*s == t)
            return s;
        s++;
    }
    return NULL;
}
int     ft_isalnum(int c)
{
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    if(c >= '0' && c <= '9')
        return 1;
    return 0;
}
size_t  ft_strlen(const char *str)
{
    size_t l = 0;
    while(str[l])
        l++;
    return l;
}

char    *ft_strcpy(char *dest, const char *src)
{
    char *ptr = dest;
    while(*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return ptr;
}

char    *ft_strcat(char *dest, const char *src)
{
    char *ptr = dest;
    while(*dest)
        dest++;
    while(*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return ptr;
}