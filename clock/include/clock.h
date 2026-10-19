#ifndef CLOCK_H
#define CLOCK_H

#include <raylib.h>

typedef struct ClockTuning
{
    float dialSpringStrength;
    float dialDamping;
    float handSpringStrength;
    float handDamping;
} ClockTuning;

typedef struct ClockState
{
    Vector2 clockCenter;
    
    float clockRadius;
    float hourHandLength;
    float minuteHandLength;
    float secondHandLength;

    Color clockColor;
    Color bgColor;
    Color hourMarkerColor;
    Color minuteMarkerColor;
    ClockTuning tuning;

    float hourAngle;
    float minuteAngle;
    float secondAngle;
    float hourAngularVelocity;
    float minuteAngularVelocity;
    float secondAngularVelocity;
    
    // Rotation that applies only to the minute/hour marker ring.
    float dialAngle;
    float dialAngularVelocity;
    float lastDialMouseAngle;
    Vector2 dialPressMouse;

    bool draggingHour;
    bool draggingMinute;
    bool draggingSecond;
    bool draggingDial;
    bool dialWasDragged;
    bool returningHour;
    bool returningMinute;
    bool returningSecond;
} ClockState;

ClockState ClockInit(Vector2 center, int height) {
    ClockState clock;
    clock.clockCenter = center;
    clock.clockRadius = height * 0.4f;
    clock.hourHandLength = height * 0.4f * 0.5f;
    clock.minuteHandLength = height * 0.4f * 0.65f;
    clock.secondHandLength = height * 0.4f * 0.8f;
    clock.clockColor = RAYWHITE;
    clock.bgColor = (Color){31,35,53,135};
    clock.hourMarkerColor = GRAY;
    clock.minuteMarkerColor = GRAY;
    clock.tuning.dialSpringStrength = 256.0f;
    clock.tuning.dialDamping = 8.0f;
    clock.tuning.handSpringStrength = 512.0f;
    clock.tuning.handDamping = 10.0f;
    clock.hourAngle = 0.0f;
    clock.minuteAngle = 0.0f;
    clock.secondAngle = 0.0f;
    clock.hourAngularVelocity = 0.0f;
    clock.minuteAngularVelocity = 0.0f;
    clock.secondAngularVelocity = 0.0f;
    clock.dialAngle = 0.0f;
    clock.dialAngularVelocity = 0.0f;
    clock.lastDialMouseAngle = 0.0f;
    clock.dialPressMouse = center;
    clock.draggingHour = false;
    clock.draggingMinute = false;
    clock.draggingSecond = false;
    clock.draggingDial = false;
    clock.dialWasDragged = false;
    clock.returningHour = false;
    clock.returningMinute = false;
    clock.returningSecond = false;
    return clock;
}

#endif // CLOCK_H
