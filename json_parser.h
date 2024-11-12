#ifndef JSON_PARSER_H
#define JSON_PARSER_H

void read_json_data(const char *filename);
void compute_daily_averages(const char *raw_filename, const char *processed_filename, const char *date);
char *extract_json_value(const char *json, const char *key);

#endif
