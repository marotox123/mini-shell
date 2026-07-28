#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include "cd.h"
#include "utils.h"

int cd(char **argv) {
    // Zabezpiecznie jesli nie ma filepathu
    if (argv[1] == NULL) {
        return -2;
    }

    if (chdir(argv[1]) == 0) {
        return 1;
    }

    return -1;
}