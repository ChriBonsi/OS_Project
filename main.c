/**
 * @author Christian Bonsignore 110381
 */
#include <stdio.h>
#include <string.h>
#include "FileEncrypter.h"

int userAnswer;
int *intArray;
FILE *fileEncrypt;
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
            //while to get a valid filePath to a file to encrypt.
            while (fileEncrypt == NULL) {
                printf("Insert the path of the file you want to encrypt: \n");
                scanf("%s", filePath);

                if (isFileTxt(filePath, ".txt") == true) {
                    fileEncrypt = fopen(filePath, "r");
                    if (fileEncrypt == NULL) {
                        printf("Error: File not found.\n");
                    }
                }

            }
            //calls the function Encrypt.
            Encrypt(fileEncrypt);
            printf("\nThe file has been encrypted.");
        }

            //DECRYPT
        else if (userAnswer == 2) {
            //set to NULL in case of multiple executions.
            fileDecrypt = NULL;
            //while to get a valid filePath to a file to decrypt.
            while (fileDecrypt == NULL) {
                printf("Insert the path of the file you want to decrypt: \n");
                scanf("%s", filePath);

                if (isFileTxt(filePath, ".txt") == true) {
                    fileDecrypt = fopen(filePath, "r");
                }
            }
            //set to NULL in case of multiple executions.
            keyFile = NULL;
            //while to get a valid filePath to the key of the file to decrypt.
            while (keyFile == NULL) {
                printf("Insert the path of the key: \n");
                scanf("%s", filePath);

                if (isFileTxt(filePath, ".txt") == true) {
                    keyFile = fopen(filePath, "r");
                }
            }
            //calls the function getKey and gives the return to intArray.
            intArray = getKey(keyFile);

            //calls the function Decrypt.
            Decrypt(fileDecrypt, intArray);
            printf("\nThe file has been decrypted.");

            //The user wants to exit the program.
        }

            //CLOSE
        else if (userAnswer == 0) {
            //The user wants to exit so the files are closed.
            fclose(fileEncrypt);
            fclose(fileDecrypt);
            fclose(keyFile);
            printf("\nExiting the program...");
            printf("\nGoodbye.\n");
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
