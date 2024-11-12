#ifndef NOTIFICATION_H
#define NOTIFICATION_H

// Function to trigger a macOS system notification
void trigger_system_notification(const char *alert_message);

// Function to send an email with the average data
void send_email_with_daily_averages(const char *email, const char *data);

#endif
