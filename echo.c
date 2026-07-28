#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include "echo.h"
#include "utils.h"

int echo(char **argv) {
    if (argv[1] == NULL) {
        return -2;
    }

    size_t i = 1;

    while (argv[i] != NULL) {
        printf("%s ", argv[i]);
        i++;
    }
    printf("\n");
    return 1;
}