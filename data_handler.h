#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <stdio.h>
#include <stdlib.h>

// Function to write API data to file
void write_api_data_to_file(const char *filename, const char *data);

// Function to read data from file
void read_data_from_file(const char *filename);

#endif
