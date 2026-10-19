#ifndef CLOCK_TIME_H
#define CLOCK_TIME_H

#include <time.h>
#include <raylib.h>
#include "clock.h"
#include "clock_math.h"

void UpdateHandSpring(float *angle, float *angularVelocity, float targetAngle,
                      bool *returning)
{
    const float springStrength = 512.0f;
    const float damping = 10.0f;
    float dt = GetFrameTime();
    if (dt <= 0.0f) return;

    float displacement = NormalizeAngle(targetAngle - *angle);
    float acceleration = springStrength * displacement - damping * *angularVelocity;
    *angularVelocity += acceleration * dt;
    *angle += *angularVelocity * dt;

    if (fabsf(displacement) < 0.001f && fabsf(*angularVelocity) < 0.001f) {
        *angle = targetAngle;
        *angularVelocity = 0.0f;
        *returning = false;
    }
}

void UpdateClockTime(ClockState *clock) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (t == NULL) return;

    float targetHourAngle = PI - (t->tm_hour % 12)*(PI/6) - (t->tm_min / 60.0f)*(PI/6);
    float targetMinuteAngle = PI - t->tm_min * (PI/30.0f);
    float targetSecondAngle = PI - t->tm_sec * (PI/30.0f);

    if (clock->returningHour) {
        UpdateHandSpring(&clock->hourAngle, &clock->hourAngularVelocity,
                         targetHourAngle, &clock->returningHour);
    } else if (!clock->draggingHour) {
        clock->hourAngle = targetHourAngle;
    }

    if (clock->returningMinute) {
        UpdateHandSpring(&clock->minuteAngle, &clock->minuteAngularVelocity,
                         targetMinuteAngle, &clock->returningMinute);
    } else if (!clock->draggingMinute) {
        clock->minuteAngle = targetMinuteAngle;
    }

    if (clock->returningSecond) {
        UpdateHandSpring(&clock->secondAngle, &clock->secondAngularVelocity,
                         targetSecondAngle, &clock->returningSecond);
    } else if (!clock->draggingSecond) {
        clock->secondAngle = targetSecondAngle;
    }
}

#endif // CLOCK_TIME_H
