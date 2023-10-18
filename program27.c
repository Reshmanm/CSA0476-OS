#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char *dir_path;

    // Check if a directory path is provided as a command line argument
    if (argc > 1) {
        dir_path = argv[1];
    } else {
        // If no directory path is provided, use the current directory
        dir_path = ".";
    }

    // Open the directory
    DIR *directory = opendir(dir_path);

    // Check if the directory can be opened
    if (directory == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;

    // Read and print the contents of the directory
    while ((entry = readdir(directory))) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(directory);

    return 0;
}
