/**
 * @author Christian Bonsignore 110381
 */
#include "FileEncrypter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

FILE *tempFile;
FILE *fileHandler;
char accessO[N];
char accessG[N];
char accessU[N];
int keyArray[5];
char buffer[N];
char buffer1[N];

char filePath[N]; // Definition of the filePath variable


/**
 * It generates a random key made of 5 digits and saves each one of them
 * in a file (separated by a comma). In the end it changes the access permissions
 * of the key file so that only the user owner can read it.
 */
void generateRandomKey() {
    int randomNumber = 0;

    //Keeps generating a randomNumber until it has 5 digits.
    while (randomNumber < 10000) {
        //gets the time in seconds and uses it to generate a random number.
        int t = time(NULL);
        randomNumber = 10000 + t;
        //abs makes the number of 5 digits (obtained as a result from %99999),
        // generated by the sum of rand() and randomNumber, positive.
        randomNumber = abs((rand() + randomNumber) % (99999));
    }

    //Set to NULL in case of multiple computations.
    fileHandler = NULL;

    //Insert, through user input, the filePath of the key to use.
    while (fileHandler == NULL) {
        printf("Insert the filePath where the key will be saved: \n");
        scanf("%s", filePath);
        //Takes only the last 4 characters of the filePath.
        char *last_four = &filePath[strlen(filePath) - 4];
        //Checks if the file is a .txt file comparing the last 4 characters with .txt.
        if (strcmp(last_four, ".txt") == 0) {
            //checks if there is already a file with the same name within that filePath.
            if (access(filePath, 0) == 0) {
                printf("\nIt already exists a file with this name.\n");
                //used it to make the cycle repeat.
                fileHandler = NULL;
            } else {
                fileHandler = fopen(filePath, "w");
            }
        }
    }

    //separates the digits of the number generated and writes them to the keyFile
    //separated by commas.
    keyArray[4] = randomNumber % 10;
    keyArray[3] = (randomNumber) % 100 / 10;
    keyArray[2] = (randomNumber) % 1000 / 100;
    keyArray[1] = (randomNumber) % 10000 / 1000;
    keyArray[0] = randomNumber / 10000;
    char separator[] = ",";
    fprintf(fileHandler, "%d", keyArray[0]);
    fprintf(fileHandler, "%c", separator[0]);
    fprintf(fileHandler, "%d", keyArray[1]);
    fprintf(fileHandler, "%c", separator[0]);
    fprintf(fileHandler, "%d", keyArray[2]);
    fprintf(fileHandler, "%c", separator[0]);
    fprintf(fileHandler, "%d", keyArray[3]);
    fprintf(fileHandler, "%c", separator[0]);
    fprintf(fileHandler, "%d", keyArray[4]);
    fclose(fileHandler);
    //file access permissions
    sprintf(accessO, "chmod o=--- %s", filePath);
    system(accessO);
    sprintf(accessU, "chmod u=r-- %s", filePath);
    system(accessU);
    sprintf(accessG, "chmod g=--- %s", filePath);
    system(accessG);
}

/**
 * This function reads the key file and stores the key values in an array
 *
 * @param keyFile The file that contains the key.
 *
 * @return The keyArray is being returned.
 */
int *getKey(FILE *keyFile) {
    for (int i = 0; i < 5; i++) {
        fscanf(keyFile, "%d,", &keyArray[i]);
    }
    return keyArray;
}

//TODO controllare perchè taglia ultimo carattere
/**
 * At first the function checks if the pointer of the file to encrypt exists: if it doesn't, it prints
 * that the file can't be opened and returns, otherwise it keeps going.
 * After that it generates a random key and saves every character of the file in a buffer. After doing so
 * makes the user insert a filePath in which the encrypted file will be saved.
 * Then it goes through all the characters saved in the buffer; modifies them with the corresponding
 * cycling key digit, and writes them in the encrypted file.
 * In the end it sets the access permission to the file created so that everyone can only read it.
 *
 * @param readFile the file to be encrypted
 *
 */
void Encrypt(FILE *readFile) {
    if (readFile == NULL) {
        printf("\nCouldn't open the file.\n");
        return;
    }

    //Generates a random key.
    generateRandomKey();

    //A while cycle that reads every line of the readFile (saves them to buffer1)
    //and appends them in buffer (thanks to buffer1).
    while (fgets(buffer1, N, readFile)) {
        printf("line: %s", buffer1);
        strcat(buffer, buffer1);
    }

    //Set to NULL in case of multiple computations.
    tempFile = NULL;

    //Insert, through user input, the filePath of the encrypted file to create.
    while (tempFile == NULL) {
        printf("Insert the filePath where you want to save the encrypted file: \n");
        scanf("%s", filePath);
        //Takes only the last 4 characters of the filePath.
        char *last_four = &filePath[strlen(filePath) - 4];
        //Checks if the file is a .txt file comparing the last 4 characters with .txt.
        if (strcmp(last_four, ".txt") == 0) {
            //checks if there is already a file with the same name within that filePath.
            if (access(filePath, 0) == 0) {
                printf("It already exists a file with this name.");
                //used it to make the cycle repeat.
                tempFile = NULL;
            } else {
                tempFile = fopen(filePath, "w");
            }
        }
    }

    //The pointer is at the end of the file because the file has already been read by fgets.
    int effectiveFileLength = ftell(readFile);
    //Count is used to go through the keyArray.
    int count = 0;
    //We go through the buffer until the character before \0 (EOF), and we encrypt it while cycling the key.
    for (int i = 0; i < effectiveFileLength - 1; i++) {
        //Writes to the encrypted file the character obtained from the sum of the character and key.
        fprintf(tempFile, "%c", buffer[i] + keyArray[count]);
        //Used it to cycle the key.
        if (count == 4) {
            count = -1;
        }
        count++;
    }
    fclose(tempFile);
    //Change the permission access to the encrypted file.
    sprintf(accessO, "chmod o=r-- %s", filePath);
    system(accessO);
    sprintf(accessU, "chmod u=r-- %s", filePath);
    system(accessU);
    sprintf(accessG, "chmod g=r-- %s", filePath);
    system(accessG);
    //sets all elements of buffer and buffer1 to NULL.
    memset(buffer, 0, strlen(buffer));
    memset(buffer1, 0, strlen(buffer1));
}

/**
 * At first the function checks if the pointer of the file to decrypt exists: if it doesn't, it prints
 * that the file can't be opened and returns, otherwise it keeps going. After that, it saves every
 * character of the file in a buffer and makes the user insert a filePath in which the decrypted file
 * will be saved. Then it goes through all the characters saved in the buffer;
 * modifies them with the corresponding cycling key digit, and writes them in the decrypted file.
 * In the end it sets the access permission to the file created so that only the file's owner can
 * read it.
 *
 * @param readFile The file we want to read from.
 * @param keyBuffer The key used to previously encrypt the file.
 *
 */
void Decrypt(FILE *readFile, int *keyBuffer) {
    if (readFile == NULL) {
        printf("\nCouldn't open the file.\n");
        return;
    }

    //A while cycle that reads every line of the readFile (saves them to buffer1)
    //and appends them in buffer (thanks to buffer1).
    while (fgets(buffer1, N, readFile)) {
        strcat(buffer, buffer1);
    }

    //Set to NULL in case of multiple computations.
    tempFile = NULL;

    //Insert, through user input, the filePath of the decrypted file to create.
    while (tempFile == NULL) {
        printf("Insert the filePath where you want to save the decrypted file: \n");
        scanf("%s", filePath);
        //Takes only the last 4 characters of the filePath.
        char *last_four = &filePath[strlen(filePath) - 4];
        //Checks if the file is a .txt file comparing the last 4 characters with .txt.
        if (strcmp(last_four, ".txt") == 0) {
            //checks if there is already a file with the same name within that filePath.
            if (access(filePath, 0) == 0) {
                printf("It already exists a file with this name.");
                //used it to make the cycle repeat.
                tempFile = NULL;
            } else {
                tempFile = fopen(filePath, "w");
            }
        }
    }

    //The pointer is at the end of the file because the file has already been read by fgets.
    int effectiveFileLength = ftell(readFile);

    //Count is used to go through the keyBuffer.
    int count = 0;
    //We go through the buffer, and we decrypt it using the same key used to encrypt it.
    for (int i = 0; i < effectiveFileLength; i++) {
        //written the character obtained from the subtraction of the character saved
        //in the buffer and the key into the decrypted file.
        fprintf(tempFile, "%c", buffer[i] - keyBuffer[count]);
        //Used it to cycle the key.
        if (count == 4) {
            count = -1;
        }
        count++;
    }
    fclose(tempFile);
    //Changes the access permissions of the decrypted file.
    sprintf(accessO, "chmod o=--- %s", filePath);
    system(accessO);
    sprintf(accessU, "chmod u=r-- %s", filePath);
    system(accessU);
    sprintf(accessG, "chmod g=--- %s", filePath);
    system(accessG);
    //sets all elements of buffer and buffer1 to NULL.
    memset(buffer, 0, strlen(buffer));
    memset(buffer1, 0, strlen(buffer1));
}

/**
 * This function checks if the file has the required extension.
 *
 * @param pathForFile The path of the file to check.
 * @param fileExtension The extension of the file to check.
 *
 * @return true if the file is of the right extension, false otherwise.
 */
bool isFileTxt(char *pathForFile, char *fileExtension) {
    //Takes only the last 4 characters of the filePath.
    char *last_four = &pathForFile[strlen(pathForFile) - 4];
    //printf("%s\n", last_four);

    //Checks if the file is a .txt file comparing the last 4 characters with .txt.
    if (strcmp(last_four, fileExtension) == 0) {
        printf("The file is a .txt file.\n");
        return true;
    }
    printf("The file is not a .txt file.\n");
    return false;
}
