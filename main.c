#include "json_parser.h"
#include "data_handler.h"
#include "notification.h"
#include <string.h>

void simulate_api_call(const char *filename) {
    const char *data = "{\"date\":\"11-11-2024\", \"co\":\"0.3\", \"no2\":\"12\", \"o3\":\"35\", \"so2\":\"0.5\", \"pm2_5\":\"15\", \"pm10\":\"20\", \"us_epa_index\":\"3\", \"gb_defra_index\":\"1.5\"}";
    write_api_data_to_file(filename, data);
}

int main() {
    const char *filename = "raw_data.txt";  // File where the API data will be saved
    const char *date_to_find = "11-11-2024";
    const char *email = "manahiladeel09@gmail.com";  // Replace with your email address

    printf("Simulating API call...\n");
    simulate_api_call(filename);

    printf("Computing daily averages...\n");
    compute_daily_averages(filename, "processed_data.txt", date_to_find, email);

    return 0;
}
