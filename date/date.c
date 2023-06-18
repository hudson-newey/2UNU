#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "date.h"

char* getWeekdayString(int index) {
    char const *weekdays[] = {
        "Sun",
        "Mon",
        "Tue",
        "Wed",
        "Thu",
        "Fri",
        "Sat"
    };

    return weekdays[index];
}

char* getMonthString(int index) {
    char const *months[] = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };

    return months[index];
}

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

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int hour = tm.tm_hour;
    bool isPm = hour > 12;
    char amPmText[8] = "AM";

    if (hour > 12) {
        strcpy(amPmText, "PM");
    }

    // TODO: this always shows AEST. I should probably derive this somehow
    printf("%s %s %d %d:%d:%d %s AEST %d\n",
        getWeekdayString(tm.tm_wday),
        getMonthString(tm.tm_mon),
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec,
        amPmText,
        tm.tm_year + 1900
    );

    return 0;
}
