#ifndef CLOCK_TIME_H
#define CLOCK_TIME_H

#include <time.h>
#include <raylib.h>
#include "clock.h"

void UpdateClockTime(ClockState *clock) {
    if (clock->draggingHour || clock->draggingMinute || clock->draggingSecond) {
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (t == NULL) return;

    clock->hourAngle = PI - (t->tm_hour % 12)*(PI/6) - (t->tm_min / 60.0f)*(PI/6);
    clock->minuteAngle = PI - t->tm_min * (PI/30.0f);
    clock->secondAngle = PI - t->tm_sec * (PI/30.0f);
}

#endif // CLOCK_TIME_H