#include "json_parser.h"
#include "notification.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "network.h"

int main() {
    const char *filename = "raw_data.txt";

    // Get the current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Format the date as "dd-mm-yyyy"
    char current_date[11];
    snprintf(current_date, sizeof(current_date), "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    printf("Current date: %s\n", current_date);

    printf("Computing daily averages...\n");
    compute_daily_averages(filename, "processed_data.txt", current_date);

    return 0;
}
