#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "mkdir.h"

int cmd_mkdir(char **argv) {
    if (argv[1] == NULL) {
        return -1;
    }
    size_t i = 1;
    while (argv[i] != NULL) {
        if (mkdir(argv[i], 0755) != 0) {
            perror("mkdir");
            return -1;
        }
        i++;
    }
    return 1;
}