/**
 * @author Christian Bonsignore 110381
 */
#include <stdio.h>
#include <stdbool.h>

#define N 40000
extern char filePath[N]; // Declaration of the filePath variable


#ifndef OS_PROJECT_FILE_ENCRYPTER_H
#define OS_PROJECT_FILE_ENCRYPTER_H
#endif //OS_PROJECT_FILE_ENCRYPTER_H

/**
 * It reads the file, generates a random key, and then encrypts the file in a new file.
 * @param readFile the file to be encrypted
 */
void Encrypt(FILE *readFile);

/**
 * It reads an encrypted file, takes the associated key and decrypts it.
 * @param readFile The file we want to read from.
 * @param keyBuffer The key used to previously encrypt the file.
 */
void Decrypt(FILE *readFile, int *keyBuffer);

/**
 * It generates a random key made of 5 digits and saves each one of them
 * in a file (separated by a comma).
 */
void generateRandomKey();

/**
 * This function reads the key file and stores the key values in an array
 * @param keyFile The file that contains the key.
 * @return The keyArray is being returned.
 */
int *getKey(FILE *keyFile);

/**
 * This function takes only the last 4 characters of the filePath and
 * checks if it is the desired format.
 * @param file The file to be checked.
 * @return True if the file is empty, false otherwise.
 */
bool isFileTxt(char *pathForFile, char *fileExtension);
