/**
 * @author Christian Bonsignore 110381
 */
#include <stdio.h>
#include <string.h>
#include "FileEncrypter.h"

#define N 40000
int userAnswer;
int *intArray;
FILE *fileEncrypt;
char path[N];
FILE *fileDecrypt;
FILE *keyFile;


int main() {

    //var used to repeat the first while.
    int cycle = 1;

    printf("Welcome to The File Encrypt:\n");
    printf("   - Insert 1 to encrypt a file.\n");
    printf("   - Insert 2 to decrypt a file.\n");
    printf("   - Insert 0 to exit the program.\n");

    scanf("%d", &userAnswer);

    while (cycle == 1) {
        //ENCRYPT
        if (userAnswer == 1) {
            //set to NULL in case of multiple executions.
            fileEncrypt = NULL;
            //while to get a valid path to a file to encrypt.
            while (fileEncrypt == NULL) {
                printf("Insert the path of the file you want to encrypt: \n");
                scanf("%s", path);

                if(isFileTxt(path, ".txt") == true){
                    fileEncrypt = fopen(path, "r");

                    //calls the function Encrypt.
                    //Encrypt(fileEncrypt);
                    printf("\nThe file has been encrypted.");
                }
                //Takes only the last 4 characters of the path.
                char *last_four = &path[strlen(path) - 4];
                //Checks if the file is a .txt file comparing the last 4 characters with .txt.
                if (strcmp(last_four, ".txt") == 0) {
                    fileEncrypt = fopen(path, "r");
                }
            }
            //calls the function Encrypt.
            //Encrypt(fileEncrypt);
            printf("\nThe file has been encrypted.");

            //The user wants to decrypt a file.
        }

        //DECRYPT
        else if (userAnswer == 2) {
            //set to NULL in case of multiple executions.
            fileDecrypt = NULL;
            //while to get a valid path to a file to decrypt.
            while (fileDecrypt == NULL) {
                printf("Insert the path of the file you want to Decrypt: \n");
                scanf("%s", path);
                //while to get a valid path to a file to encrypt.
                char *last_four = &path[strlen(path) - 4];
                //Checks if the file is a .txt file comparing the last 4 characters with .txt.
                if (strcmp(last_four, ".txt") == 0) {
                    fileDecrypt = fopen(path, "r");
                }
            }
            //set to NULL in case of multiple executions.
            keyFile = NULL;
            //while to get a valid path to the key of the file to decrypt.
            while (keyFile == NULL) {
                printf("Insert the path of the key: \n");
                scanf("%s", path);
                //Checks if the file is a .txt file comparing the last 4 characters with .txt.
                char *last_four = &path[strlen(path) - 4];
                if (strcmp(last_four, ".txt") == 0) {
                    keyFile = fopen(path, "r");
                }
            }
            //calls the function getKey and gives the return to intArray.
            //TODO intArray = getKey(keyFile);

            //calls the function Decrypt.
            //TODO Decrypt(fileDecrypt, intArray);
            printf("\nThe file has been decrypted.");

            //The user wants to exit the program.
        }

        //BRUTE FORCE
        //TODO
        else if (userAnswer == 3) {}

        //OTHER
        else if (userAnswer == 0) {
            //The user wants to exit so the files are closed.
            fclose(fileEncrypt);
            fclose(fileDecrypt);
            fclose(keyFile);
            printf("\nExiting the program...");
            printf("\nGoodbye.");
            return 0;
        }

        //EVERYTHING ELSE
        printf("\nDo you want to do something else? Insert 1 to select a new action or 0 to exit the program.\n");
        scanf("%d", &cycle);
        //The user wants to encrypt or decrypt a new file.
        if (cycle == 1) {
            printf("   - Insert 1 to encrypt a file.\n");
            printf("   - Insert 2 to decrypt a file.\n");
            printf("   - Insert 0 to exit the program.\n");
            scanf("%d", &userAnswer);
        } else {
            printf("\nExiting the program...");
            printf("\nGoodbye.");
            return 0;
        }
    }
    //Before ending the computation the files are closed.
    fclose(fileEncrypt);
    fclose(fileDecrypt);
    fclose(keyFile);
    return 0;
}
