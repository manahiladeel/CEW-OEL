#include "data_handler.h"

void write_api_data_to_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a"); // Open file in write mode
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    // Write the data to the file
    fprintf(file, "%s\n", data);

    fclose(file); // Close the file
    printf("Data written to %s successfully.\n", filename);
}

void read_data_from_file(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open file in read mode
    if (!file) {
        perror("Error opening file for reading");
        return;
    }

    char line[256];
    printf("Reading data from %s:\n\n", filename);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Print each line
    }

    fclose(file); // Close the file
}
