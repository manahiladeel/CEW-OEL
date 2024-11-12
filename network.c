#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "network.h"

void save_json_data(const char *filename, const char *location_name, const char *region,
                    const char *country, const char *co, const char *no2, const char *o3,
                    const char *so2, const char *pm2_5, const char *pm10,
                    const char *us_epa_index, const char *gb_defra_index) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    time_t t = time(NULL);
    struct tm *currentDate = localtime(&t);
    char date[11];
    snprintf(date, sizeof(date), "%02d-%02d-%d", currentDate->tm_mday, currentDate->tm_mon + 1, currentDate->tm_year + 1900);

    fprintf(file, "{\"location\": {\"name\": \"%s\", \"region\": \"%s\", \"country\": \"%s\", \"date\": \"%s\"}, "
                  "\"air_quality\": {\"co\": \"%s\", \"no2\": \"%s\", \"o3\": \"%s\", \"so2\": \"%s\", "
                  "\"pm2_5\": \"%s\", \"pm10\": \"%s\"}, \"indices\": {\"us_epa_index\": \"%s\", "
                  "\"gb_defra_index\": \"%s\"}}\n",
            location_name, region, country, date, co, no2, o3, so2, pm2_5, pm10, us_epa_index, gb_defra_index);

    fclose(file);
}
