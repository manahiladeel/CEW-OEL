#ifndef NETWORK_H
#define NETWORK_H

void save_json_data(const char *filename, const char *location_name, const char *region,
                    const char *country, const char *co, const char *no2, const char *o3,
                    const char *so2, const char *pm2_5, const char *pm10,
                    const char *us_epa_index, const char *gb_defra_index);

#endif
