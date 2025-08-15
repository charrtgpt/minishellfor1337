#include "minishell.h"

int main()
{
    int fd[2];
    char buffer[100];
    char sbuffer[100];
    char tbuffer[100];


    pipe(fd);
    int a = dup(STDOUT_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    write(1, "123456789\n", 10);
    dup2(a, STDOUT_FILENO);
    close(fd[1]);
    int c = dup(fd[0]);
    int i = read(fd[0], buffer, 2);
    buffer[i] = '\0';
    printf("\n%s\n", buffer);

    i = read(fd[0], buffer, 2);
    buffer[i] = '\0';
    printf("\n%s\n", buffer);

    i = read(c, sbuffer, 2);
    sbuffer[i] = '\0';
    printf("\n%s\n", sbuffer);
    printf("\n>>>>>>>>  %d  >>>>>>>>>\n\n>>>>>>>>  %d  >>>>>>>>>\n", fd[0], c);

     printf("\n>>>>>>>>>>>>>>>>>\n\n>>>>>>>>>>>>>>>>>\n");
    int lawal = open("tropic.txt", O_CREAT | O_TRUNC | O_RDWR);
    int tani = open("tropic.txt", O_RDWR);
    write(lawal, "\nzzzzzzzzzz\n", 12);


    int z = read(tani, tbuffer, 10);
    write(lawal, "\nYOUSSEF\n", 9);
    tbuffer[z] = '\0';
    printf("\n%s\n", tbuffer);


}