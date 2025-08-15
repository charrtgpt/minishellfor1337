#include <stdio.h>

typedef enum e_rtype
{
	RED_OUT = -2,
	RED_APPEND,
	RED_IN,
	RED_HEREDOC
}	t_rtype;

int main()
{
    printf("%d\n", RED_OUT);
    printf("%d\n", RED_APPEND);
    printf("%d\n", RED_IN);
    printf("%d\n", RED_HEREDOC);
    printf("%d\n", RED_OUT);
    return(0);
}