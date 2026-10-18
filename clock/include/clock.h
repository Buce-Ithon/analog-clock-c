#ifndef CLOCK_H
#define CLOCK_H

#include <raylib.h>

typedef struct ClockState
{
    Vector2 clockCenter;
    
    float clockRadius;
    float hourHandLength;
    float minuteHandLength;
    float secondHandLength;

    Color clockColor;
    Color bgColor;

    float hourAngle;
    float minuteAngle;
    float secondAngle;
    
    bool draggingHour;
    bool draggingMinute;
    bool draggingSecond;
} ClockState;

ClockState ClockInit(Vector2 center, int height) {
    ClockState clock;
    clock.clockCenter = center;
    clock.clockRadius = height * 0.4f;
    clock.hourHandLength = height * 0.4f * 0.5f;
    clock.minuteHandLength = height * 0.4f * 0.65f;
    clock.secondHandLength = height * 0.4f * 0.8f;
    clock.clockColor = RAYWHITE;
    clock.bgColor = (Color){31,35,53,255};
    clock.hourAngle = 0.0f;
    clock.minuteAngle = 0.0f;
    clock.secondAngle = 0.0f;
    clock.draggingHour = false;
    clock.draggingMinute = false;
    clock.draggingSecond = false;
    return clock;
}


#endif // CLOCK_H