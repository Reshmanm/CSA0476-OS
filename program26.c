#include <stdio.h>

int main() {
    FILE *file; // Declare a file pointer
    char data[100]; // Buffer to hold data

    // Create a file and write data to it
    file = fopen("sample.txt", "w"); // "w" for write mode
    if (file == NULL) {
        printf("File could not be opened.\n");
        return 1;
    }

    fprintf(file, "Hello, World!\n");
    fprintf(file, "This is a sample file.\n");
    fclose(file); // Close the file

    // Open the file for reading
    file = fopen("sample.txt", "r"); // "r" for read mode
    if (file == NULL) {
        printf("File could not be opened for reading.\n");
        return 1;
    }

    // Read and display the contents of the file
    printf("Contents of the file:\n");
    while (fgets(data, sizeof(data), file) != NULL) {
        printf("%s", data);
    }

    fclose(file); // Close the file

    // Append data to the file
    file = fopen("sample.txt", "a"); // "a" for append mode
    if (file == NULL) {
        printf("File could not be opened for appending.\n");
        return 1;
    }

    fprintf(file, "Appending more data to the file.\n");
    fclose(file); // Close the file

    // Reopen the file for reading
    file = fopen("sample.txt", "r");
    if (file == NULL) {
        printf("File could not be opened for reading.\n");
        return 1;
    }

    // Read and display the updated contents of the file
    printf("\nUpdated contents of the file:\n");
    while (fgets(data, sizeof(data), file) != NULL) {
        printf("%s", data);
    }

    fclose(file); // Close the file

    return 0;
}
