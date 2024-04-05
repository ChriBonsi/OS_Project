/**
 * @author Christian Bonsignore 110381
 */
#include "FileEncrypter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define N 40000

bool isFileTxt(char *filePath, char *fileExtension) {
    //Takes only the last 4 characters of the path.
    char *last_four = &filePath[strlen(filePath) - 4];
    //Checks if the file is a .txt file comparing the last 4 characters with .txt.
    if (strcmp(last_four, fileExtension) == 0) {
        printf("The file is a .txt file.\n");
        return true;
    }
    printf("The file is not a .txt file.\n");
    return false;
}