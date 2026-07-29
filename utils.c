#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include "utils.h"

static const char *komendy[] = {
    "help",
    "clear",
    "pwd",
    "cd",
    "ls",
    "exit",
    "echo",
    "mkdir",
    "..",
    "touch"
};

char **ArgumentParser(const char *buffer) {
    size_t cap = 8; 
    size_t i = 0;
    char **argv = malloc(sizeof(char*) * cap); // auto limit
    if (argv == NULL) return NULL;
    int argc = 0;
    while (buffer[i] != '\0') {
        while (isspace((unsigned char)buffer[i])) {
            i++;
        }
        if (buffer[i] == '\0') break;

        size_t start = i;
        while (buffer[i] != '\0' && !isspace((unsigned char)buffer[i])) {
            i++;
        }
        size_t len = i - start;
        if ((size_t)argc + 1 >= cap) {
            cap *= 2;
            char **tmp = realloc(argv, sizeof(char*) * cap);
            if (tmp == NULL) {
                argv[argc] = NULL;   // <- domknij listę przed free_argv
                free_argv(argv);
                return NULL;
            }
            argv = tmp;
        }
        argv[argc] = malloc(len + 1);
        memcpy(argv[argc], buffer + start, len);
        argv[argc][len] = '\0';
        argc++;
    }
    argv[argc] = NULL;
    return argv;
}

int commandcheck(char **argv) {
    if (argv == NULL || argv[0] == NULL) {
        return -1;
    }

    size_t liczba_komend = sizeof(komendy) / sizeof(komendy[0]);
    for (size_t j = 0; j < liczba_komend; j++) {
        if (strcmp(argv[0], komendy[j]) == 0) {
            return (int)j;
        }
    }
    return -1;
}

int executablecheck(char **argv) {
    if (argv == NULL || argv[0] == NULL) {
        return -1;
    }
    if (strncmp(argv[0], "./", 2) == 0) {
        return 1;
    }
    return 0;
}

void free_argv(char **argv) {
    if (argv == NULL) return;

    for (int i = 0; argv[i] != NULL; i++) {
        free(argv[i]);
    }

    free(argv);
}

void clearbuffer(char *buffer, size_t *sizedirect) {
    for (size_t i = 0; i < *sizedirect; i++) {
        buffer[i] = '\0';
    }
}

bool czy_sciezka_istnieje(const char *path) {
    struct stat info;

    // Sprawdzenie czy ścieżka w ogóle istnieje
    if (stat(path, &info) != 0) {
        return false; 
    }

    // Opcjonalnie: Sprawdzenie czy to jest katalog (folder)
    return S_ISDIR(info.st_mode);
}

void odswiez_sciezke(char **dir_ptr) {
    if (dir_ptr == NULL) return;
    
    free(*dir_ptr);             // Zwolnij to, na co wskazuje directory
    *dir_ptr = getcwd(NULL, 0); // Przypisz nową pamięć
}