#include "json_parser.h"
#include "data_handler.h"
#include "notification.h"
#include <string.h>
#include "network.h"

int main() {
    const char *filename = "raw_data.txt";
    const char *date_to_find = "13-11-2024";

    printf("Computing daily averages...\n");
    compute_daily_averages(filename, "processed_data.txt", date_to_find);
    

    return 0;
}
