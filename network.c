#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>
#include "json_parser.h"
#include "notification.h"

// Struct for handling the response data from the API
struct Memory {
    char *response;
    size_t size;
};

// Callback function to handle data received by CURL
static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if (ptr == NULL) {
        fprintf(stderr, "Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = '\0';

    return realsize;
}

// Fetch JSON data from URL
char* fetch_url(const char* url) {
    CURL *curl;
    CURLcode res;
    struct Memory chunk = { .response = NULL, .size = 0 };

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return NULL;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        free(chunk.response);
        chunk.response = NULL;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return chunk.response;
}


// Function to fetch, extract, format, and write data to raw_data.txt
void fetch_and_save_weather_data(const char *url, const char *filename) {
    // Fetch data from API
    char *json_data = fetch_url(url);
    if (!json_data) {
        fprintf(stderr, "Failed to fetch weather data.\n");
        return;
    }

    // Extract required values
    char *location_name = extract_json_value(json_data, "\"name\"");
    char *region = extract_json_value(json_data, "\"region\"");
    char *country = extract_json_value(json_data, "\"country\"");
    char *co = extract_json_value(json_data, "\"co\"");
    char *no2 = extract_json_value(json_data, "\"no2\"");
    char *o3 = extract_json_value(json_data, "\"o3\"");
    char *so2 = extract_json_value(json_data, "\"so2\"");
    char *pm2_5 = extract_json_value(json_data, "\"pm2_5\"");
    char *pm10 = extract_json_value(json_data, "\"pm10\"");
    char *us_epa_index = extract_json_value(json_data, "\"us-epa-index\"");
    char *gb_defra_index = extract_json_value(json_data, "\"gb-defra-index\"");
    double us__index = strtod(us_epa_index, NULL);
    double gb__index = strtod(gb_defra_index, NULL);

    // Get current date in dd-mm-yyyy format
    time_t t = time(NULL);
    struct tm *currentDate = localtime(&t);
    char date[11];
    snprintf(date, sizeof(date), "%02d-%02d-%d", currentDate->tm_mday, currentDate->tm_mon + 1, currentDate->tm_year + 1900);
    if (gb__index > 3.5) {
        trigger_system_notification("Warning: GB Index is high!");
    }
    if (us__index > 10.2) {
        trigger_system_notification("Warning: EPA Index is high!");
    }


    // Format data as specified JSON structure
    FILE *file = fopen(filename, "a");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        free(json_data);
        return;
    }
 fprintf(file, "{\"location\": {\"name\": \"%s\", \"region\": \"%s\", \"country\": \"%s\", \"date\": \"%s\"}, "
                  "\"air_quality\": {\"co\": \"%s\", \"no2\": \"%s\", \"o3\": \"%s\", \"so2\": \"%s\", "
                  "\"pm2_5\": \"%s\", \"pm10\": \"%s\"}, \"indices\": {\"us_epa_index\": \"%s\", "
                  "\"gb_defra_index\": \"%s\"}}\n",
            location_name ? location_name : "N/A",
            region ? region : "N/A",
            country ? country : "N/A",
            date,
            co,
            no2,
            o3,
            so2,
            pm2_5,
            pm10,
            us_epa_index,
            gb_defra_index);

    fclose(file);
    // Free memory
    free(json_data);
    free(location_name); free(region); free(country);
    free(co); free(no2); free(o3); free(so2); free(pm2_5); free(pm10);
    free(us_epa_index); free(gb_defra_index);
}
