#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_parser.h"  // Includes declaration for compute_daily_averages and other functions

int main() {
    const char *date_to_find = "12-11-2024";
    
    // Call the function
    compute_daily_averages("raw_data.txt", "processed_data.txt", date_to_find);

    return 0;
}
