#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to trigger macOS notification
void trigger_system_notification(const char *alert_message) {
    // Construct the AppleScript command to trigger the notification
    char command[512];
    snprintf(command, sizeof(command), "osascript -e 'display notification \"%s\" with title \"API Alert\"'", alert_message);

    // Execute the AppleScript command
    system(command);
}
