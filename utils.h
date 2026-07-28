#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>

char **ArgumentParser(const char *buffer);
int commandcheck(char **argv);
void free_argv(char **argv);
void clearbuffer(char *buffer, size_t *sizedirect);
bool czy_sciezka_istnieje(const char *path);
void odswiez_sciezke(char **dir_ptr);
int executablecheck(char **argv);
#endif