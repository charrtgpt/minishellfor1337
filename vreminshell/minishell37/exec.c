#include "header.h"

int heredoc(const char *delimiter)
{
    char *line = NULL;
    int fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            write(1, "\n", 1);
            break;
        }
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }

    close(fd);

    fd = open("/tmp/.heredoc_tmp", O_RDONLY);
    if (fd < 0)
    {
        perror("open for read");
        return -1;
    }
    return fd;
}

void execute_command(t_cmd *cmd)
{
    if (cmd->heredoc)
    {
        int heredoc_fd = heredoc(cmd->heredoc);
        if (heredoc_fd == -1)
        {
            printf("Couldn't handle heredoc\n");
            return;
        }

        dup2(heredoc_fd, STDIN_FILENO);
        close(heredoc_fd);
    }

    printf("Command ready to execute with heredoc as input.\n");
    char buffer[1024];
    int n = read(STDIN_FILENO, buffer, 1023);
    if (n > 0)
    {
        buffer[n] = '\0';
        printf("Heredoc content:\n%s", buffer);
    }
}