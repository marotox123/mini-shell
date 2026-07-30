#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pwd.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <ctype.h>
#include "cd.h"
#include "utils.h"
#include "echo.h"
#include "ls.h"
#include "mkdir.h"
#include "touch.h"
#include "runelf.h"

volatile sig_atomic_t got_sigint = 0;

void handle_ctrl_c(int sig) {
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    got_sigint = 1;
}

int main(void) {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    const char *user = strdup(pw->pw_name);
    char hostname[HOST_NAME_MAX + 1];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        // nic tu
    } else {
        perror("gethostname");
        return 1;
    }
    size_t cap = 8;          // pojemność
    size_t len = 0;          // ile znaków mamy
    char *buf = malloc(cap);
    if (buf == NULL) return 1;
    char *directory = getcwd(NULL, 0);
    if (directory == NULL) {
        perror("getcwd");
        return 1;
    }
    struct sigaction sa;
    sa.sa_handler = handle_ctrl_c;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; // Brak SA_RESTART - przerwany read() ma zwrocic EINTR
    sigaction(SIGINT, &sa, NULL);
    while (1) {
       len = 0;
       odswiez_sciezke(&directory);
       printf("%s@%s %s>", user, hostname, directory);
       int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        // potrzebujemy miejsca na znak + '\0'
            if (len + 1 >= cap) {
                size_t new_cap = cap * 2;
                char *tmp = realloc(buf, new_cap);
                if (tmp == NULL) {
                    free(buf);
                    return 1;
                }
                buf = tmp;
                cap = new_cap;
            }   

            buf[len++] = (char)ch;
        }
        if (got_sigint) {
            got_sigint = 0;
            clearerr(stdin); // zdejmujemy flage bledu ustawiona przez przerwany read()
            continue;        // porzucamy wpisywana linie, nowy prompt
        }
        buf[len] = '\0';
        char **argv = ArgumentParser(buf);
        int idx = commandcheck(argv);
        switch (idx)
        {
        case -1:
            if (executablecheck(argv) == 1) {
               if (run_executable(argv) == -1) {
                    printf("Blad uruchamiania programu\n"); 
               }
            } else {
               printf("Nieznana Komenda\n"); 
            }
            break;
        case 0:
            printf("Dostępne komendy: help, clear, pwd, cd, ls, exit, echo\n");
            break;

        case 1:
            printf("\e[1;1H\e[2J");
            break;

        case 2:
            printf("%s\n", directory);
            break;

        case 3: {
            int wynik = cmd_cd(argv);
            if (wynik > 0) {

            } else if (wynik == -2) {

            } else if (wynik == -1) {
                printf("cd: Ścieżka '%s' nie istnieje\n", argv[1]);
            }   
            break;
        }
        case 4:
            int ls1 = cmd_ls(argv);
            if (ls1 > 0) {

            } else if (ls1 == -2) {

            } else if (ls1 == -1) {
                printf("ls: Ścieżka '%s' nie istnieje\n", argv[1]);
            }  
            break;

        case 5:
            free((void *)user);
            free(directory);
            free_argv(argv);
            free(buf);
            exit(0);

        case 6:
            int wynik = cmd_echo(argv);
            if (wynik > 0){
            
            } else if (wynik == -2) {

            }
            break;
        case 7:
            if (cmd_mkdir(argv) != 1) {}
            break;
        case 8:
            if (chdir("..") != 0) {
                perror("chdir failed");
                break;
            }
            break;
        case 9:
            if (cmd_touch(argv) != 1) {}
            break;
        default:
            break;
        }
        clearbuffer(buf, &cap);
        free_argv(argv);
    }   
    
    free((void *)user);
    free(directory);
    free(buf);
    return 0;

}