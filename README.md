# OS_Project
Caesar cipher project developed for the Laboratory section of the Operating System course in UNICAM.
Follows the report of the project.

## Project Description
The project consists of a cipher that allows the user to encrypt and decrypt a text file using a 5-digit random key, while managing the various permissions of the generated files:
- When the user chooses to encrypt a file, they must provide the path of the file to encrypt, the path to save the key, and the path to save the encrypted file. At the end, two files are generated: the encrypted file (which can be read by everyone) and the file with the random key to decrypt the former (which can only be read by the file owner).
- When the user chooses to decrypt a file, they must provide the path of the file to decrypt, the path of the associated key, and the path to save the decrypted file. At the end, the decrypted file is generated (which can only be read by the file owner).

## Description
In implementing the project, modularity was emphasized. An implementation file and a header file were created to modularize the code. Finally, this header file was imported into the main file.
- **FileEncrypter.h**:
    - `Encrypt(FILE *readFile)`: Function that reads the input text file, generates a random key, and encrypts the file into a new one.
    - `Decrypt(FILE *readFile, int *keyBuffer)`: Function that reads the encrypted file and decrypts it into a new file using the provided key file.
    - `generateRandomKey()`: Function that generates a random 5-digit key and saves each digit into a file (separated by commas).
    - `int *getKey(FILE *keyFile)`: Function that reads the key file and saves the digits into an integer array.
    - `bool isRightFormat(char *pathForFile, char *fileExtension)`: Function that checks if the file path has the desired file format.

- **SimpleEncrypter.c**:
    - `Encrypt(FILE *readFile)`: This function first checks if the file pointer to be encrypted exists. If it does not, it returns and prints an error message. It then generates a random key and saves each character of the file into a buffer. The user is prompted to enter the path to save the encrypted file, which is repeated until the path is correct. Then, it modifies each character in the buffer by adding the corresponding key digit and writes them into the encrypted file. Finally, it sets the access permissions of the created file so that it can only be read by everyone.
    - `Decrypt(FILE *readFile, int *keyBuffer)`: Similar to `Encrypt`, this function first checks if the file pointer to be decrypted exists. If it does not, it returns and prints an error message. It then saves each character of the encrypted file into a buffer. The user is prompted to enter the path to save the decrypted file, which is repeated until the path is correct. Then, it modifies each character in the buffer by subtracting the corresponding key digit and writes them into the decrypted file. Finally, it sets the access permissions of the created file so that it can only be read by the file owner.
    - `generateRandomKey()`: This function initializes a variable `randomNumber` to 0 and enters a while loop that continues to generate a random number until it has 5 digits. It takes the current time in seconds, adds it to 10000, and assigns it to `randomNumber`. Then, it assigns the absolute value of the modulo of the sum of a random number and `randomNumber` with 99999 to `randomNumber`. Once the random number is obtained, it enters a while loop (to enter after the first time, NULL must be assigned to the fileHandler pointer outside the loop) where the user is prompted to enter a path to save the key. This is repeated until the path is correct (a .txt file is passed, and there is no existing file with that name in the same directory). Then, the digits of the previously generated number are separated (saved in an array of integers), and they are written into the corresponding file, separating each one with a comma. Finally, the permissions of the generated file (key file) are modified so that only the file owner can read it.
    - `int *getKey(FILE *keyFile)`: This function reads one digit at a time (the comma delimits the digits) from the key file and saves them into an integer array of size 5 (thanks to the `fscanf` function from `stdio.h`). Finally, it returns a pointer to the array.

The following header files are included:
- `stdio.h`: Used for file manipulation and input/output.
- `stdlib.h`: Used for process control and simple mathematical operations.
- `string.h`: Used for string manipulation and memory management.
- `time.h`: Provides standardized access to time-related functions.
- `unistd.h`: Allows access to POSIX APIs.

In addition to the header files, the symbolic constant `N = 40000` is declared, where `N` is the maximum number of characters that can be encrypted/decrypted.

- **main.c**:
    - `int main()`: Initializes a boolean variable to 1 (used when the user wants to perform multiple actions during the same program execution). Then, it prompts the user to choose between encrypting a file, decrypting a file, or exiting the program. In the first case, the user is prompted to enter the path of the file to be encrypted (initialized to NULL outside the while loop for multiple executions), which is repeated until the path is correct. Then, the `Encrypt` function defined in `EncrypterImplementation.c` is called with the newly inserted path as an argument. In the second case, instead of the path of the file to be encrypted, the user must enter the paths of the file to be decrypted and the corresponding key. Finally, if the user wants to exit the program, any open files are closed, and the program execution ends. After completing the first two cases, if the user wants, they can perform another encryption or decryption operation. Before exiting the program, any open files are closed.

The following header files are included in the main file:
- `stdio.h`: Used for file manipulation and input/output.
- `string.h`: Used for string manipulation and memory management.

In addition to the header files, the symbolic constant `N = 40000` is declared, where `N` is the maximum number of characters that can be encrypted/decrypted.
