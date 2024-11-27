#ifndef NETWORK_H
#define NETWORK_H

#include <stddef.h>

struct Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);

char* fetch_url(const char *url);


// Declaration for fetch_and_save_weather_data
void fetch_and_save_weather_data(const char *url, const char *filename);

#endif // NETWORK_H
