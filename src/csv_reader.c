#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

#define MAX_LINE_LENGTH 1024
void read_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open the file");
        return EXIT_FAILURE;
    }
    char line[MAX_LINE_LENGTH];
    string_t headers = fgets(line, sizeof(line), file);
    string_t deliminator = ",";
    while (fgets(line, sizeof(line), file)) {
        char *saveptr;
        char *token = strtok_r(line, deliminator, &saveptr);
        while (token!= NULL) {
            char *endptr;
            float num = strtof(token, &endptr);
            printf("%f ", num);
            token = strtok_r(NULL, deliminator, &saveptr);
        }
    }
    fclose(file);

}
