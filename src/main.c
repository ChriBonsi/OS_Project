#include <stdio.h>

int main() {
    FILE *fptr;

    // Create a file
    fptr = fopen("../items/newtext.txt", "w");
    //Scopri perché è segmentation fault

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1; // Return an error code indicating failure
    }

    // Write some text to the file
    fprintf(fptr, "Some text");

    // Close the file
    fclose(fptr);

    fptr = fopen("../items/newtext.txt", "r");

    if (fptr == NULL) {
        printf("Not able to open the file.");
    } else {
        // Store the content of the file
        char myString[100];

        // Read the content and store it inside myString
        while(fgets(myString, 100, fptr)) {
            printf("%s", myString);
        }

        // Close the file
        fclose(fptr);
    }

    return 0;
}
