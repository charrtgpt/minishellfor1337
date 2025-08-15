#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    printf("\nzzzzzzzzz\n");
    printf("\nt%d\n", pid);

    if (pid == 0) {
        // Child process
        printf("Child running...\n");
        sleep(2);
        printf("Child exiting\n");
        return 42;
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);  // Waits for that child
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}