#include "json_parser.h"
#include "notification.h"
#include <string.h>
#include "network.h"

int main() {
    const char *filename = "raw_data.txt";  // File where the API data will be saved
    const char *url = "http://api.weatherapi.com/v1/forecast.json?key=8cfd8037b9af4ff4a6394316241408&q=Karachi&aqi=yes";

    fetch_and_save_weather_data(url, filename);

    return 0;
}
