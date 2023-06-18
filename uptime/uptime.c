#include <stdio.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <time.h>
#include "uptime.h"

int main(int argc, char const *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("%s\n", version);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("%s\n", helpDocs);
            return 0;
        }
    }

    // get the current time
    // this is displayed at the start of the output
    time_t currentTime;
    time(&currentTime);
    struct tm *timeInfo = localtime(&currentTime);

    // get the current system uptime
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        printf("Error: failed to get system info\n");
        return 1;
    }

    long uptimeSeconds = info.uptime;

    // since we use a greedy algorithm to calculate the uptime in days, hours, and minutes
    // we want to use the modulus
    long uptimeMinutes = uptimeSeconds % 60;
    long uptimeHours = (uptimeSeconds / 60) % 60;
    long uptimeDays = ((uptimeSeconds / 60) / 60) % 24;

    // these are currently hard coded and incorrect
    printf("This command is currently incomplete. Please do not use it...");
    printf("%d:%d:%d  up %ld days  %d:%d, 3 users, load average: 0.76, 0.87, 0.8\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, uptimeDays, uptimeHours, uptimeMinutes);

    return 0;
}
