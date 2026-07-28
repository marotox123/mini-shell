#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "ls.h"
#include "utils.h"

int cmd_ls(char **argv) {
    DIR *d;
    struct dirent *dir;
    if (argv[1] == NULL) {
        d = opendir(".");
        if (d == NULL) {
            return -1;
        }
    } else {
        d = opendir(argv[1]);
        if (d == NULL) {
            return -1;
        }
    }

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                printf("%s ", dir->d_name);
            }
        }
        closedir(d);
    }
    printf("\n");
    return 1;
}