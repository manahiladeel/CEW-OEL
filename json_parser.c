#include "json_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notification.h"  // Include the notification header to use the notification function


// Function to extract a value by key from a JSON line
char *extract_json_value(const char *json, const char *key) {
    char *found = strstr(json, key);
    if (found) {
        found = strchr(found, ':');
        if (found) {
            found++;  // Move past the ':'
            while (*found == ' ' || *found == '\"') found++;  // Skip spaces and quotes

            // Extract value until the next quote or comma
            char *end = found;
            while (*end && *end != '\"' && *end != ',' && *end != '}') end++;

            char *value = (char *)malloc(end - found + 1);
            strncpy(value, found, end - found);
            value[end - found] = '\0';  // Null terminate the string
            return value;
        }
    }
    return NULL;
}

#include "notification.h"

// Modified compute_daily_averages function
void compute_daily_averages(const char *raw_filename, const char *processed_filename, const char *date, const char *email) {
    FILE *file = fopen(raw_filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", raw_filename);
        return;
    }

    double total_co = 0, total_no2 = 0, total_o3 = 0, total_so2 = 0, total_pm2_5 = 0, total_pm10 = 0,
           total_gb_index = 0, total_epa = 0;
    int count = 0;
    char line[1024];
    char email_body[2048] = "";  // To store the body of the email

    while (fgets(line, sizeof(line), file)) {
        char *json_date = extract_json_value(line, "\"date\"");
        if (json_date && strcmp(json_date, date) == 0) {
            count++;
            total_co += atof(extract_json_value(line, "\"co\""));
            total_no2 += atof(extract_json_value(line, "\"no2\""));
            total_o3 += atof(extract_json_value(line, "\"o3\""));
            total_so2 += atof(extract_json_value(line, "\"so2\""));
            total_pm2_5 += atof(extract_json_value(line, "\"pm2_5\""));
            total_pm10 += atof(extract_json_value(line, "\"pm10\""));
            total_epa += atof(extract_json_value(line, "\"us_epa_index\""));
            total_gb_index += atof(extract_json_value(line, "\"gb_defra_index\""));
        }
        free(json_date);
    }
    fclose(file);

    if (count == 0) {
        printf("No data found for the specified date: %s\n", date);
        return;
    }

    FILE *output_file = fopen(processed_filename, "a");
    if (!output_file) {
        fprintf(stderr, "Error opening file %s\n", processed_filename);
        return;
    }

    fprintf(output_file, "Date: %s\n", date);
    fprintf(output_file, "Average CO: %.2f\n", total_co / count);
    fprintf(output_file, "Average NO2: %.2f\n", total_no2 / count);
    fprintf(output_file, "Average O3: %.2f\n", total_o3 / count);
    fprintf(output_file, "Average SO2: %.2f\n", total_so2 / count);
    fprintf(output_file, "Average PM2.5: %.2f\n", total_pm2_5 / count);
    fprintf(output_file, "Average PM10: %.2f\n", total_pm10 / count);
    fprintf(output_file, "Average US-EPA-INDEX: %.2f\n", total_epa / count);
    fprintf(output_file, "Average GB-DEFRA-INDEX: %.2f\n", total_gb_index / count);
    fprintf(output_file, "\n");
    fclose(output_file);

    // Generate the email body
    snprintf(email_body, sizeof(email_body),
             "Daily Averages for %s:\n\n"
             "Average CO: %.2f\n"
             "Average NO2: %.2f\n"
             "Average O3: %.2f\n"
             "Average SO2: %.2f\n"
             "Average PM2.5: %.2f\n"
             "Average PM10: %.2f\n"
             "Average US-EPA-INDEX: %.2f\n"
             "Average GB-DEFRA-INDEX: %.2f\n",
             date, total_co / count, total_no2 / count, total_o3 / count, total_so2 / count,
             total_pm2_5 / count, total_pm10 / count, total_epa / count, total_gb_index / count);

    // Send the email with the daily averages
    send_email_with_daily_averages(email, email_body);

    // Check if the indexes exceed thresholds and trigger a notification
    if (total_gb_index / count > 1.0) {
        trigger_system_notification("Warning: GB Index is high!");
    }
    if (total_epa / count > 2.0) {
        trigger_system_notification("Warning: EPA Index is high!");
    }

    printf("Count: %d\n", count);
    printf("Daily averages for %s have been computed, written to %s, and email has been sent.\n", date, processed_filename);
}
