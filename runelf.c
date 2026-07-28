#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int run_executable(char **argv) {

    if (access(argv[0], X_OK) != 0) {
        perror("access");
        return -1;
    }    
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {
        // proces dziecka
        execv(argv[0], argv);
        // jeśli execv wraca, to błąd
        perror("execv failed");
        _exit(127);
    } else {
        // proces rodzica
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}