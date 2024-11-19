#ifndef JSON_PARSER_H
#define JSON_PARSER_H

// Function to read raw JSON data
void read_json_data(const char *filename);

// Function to compu te daily averages from raw data
void compute_daily_averages(const char *raw_filename, const char *processed_filename, const char *date);

char *extract_json_value(const char *json, const char *key);
// Function to extract a value from JSON by key
// char *extract_json_value(const char *json, const char *key);

#endif
