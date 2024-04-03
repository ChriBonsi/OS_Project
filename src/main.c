#include <stdio.h>

int main() {
    FILE *fptr;

    // Create a file
    fptr = fopen("C:/Users/chri9/CLionProjects/SOLAB_Project_Bonsignore/items/newtext.txt", "w");

    // Close the file
    fclose(fptr);

    return 0;
}
