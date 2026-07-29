#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "touch.h"
#include "utils.h"

int cmd_touch(char **argv) {
    if (argv[1] == NULL) {
        return -2;
    }
    FILE *fptr;
    size_t i = 1;
    while (argv[i] != NULL) {
        fptr = fopen(argv[i], "w");
        if (fptr == NULL) {
            perror("Błąd podczas otwierania pliku");
            return 1; // Zakończenie programu z kodem błędu
        }
        fclose(fptr);
        i++;
    }
    return 1;
     
}