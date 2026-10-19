#ifndef CLOCK_INPUT_H
#define CLOCK_INPUT_H

#include <raylib.h>
#include "clock.h"
#include "clock_math.h"

#define MINUTE_MARKER_LENGTH_FACTOR 0.08f
#define DIAL_DRAG_THRESHOLD 4.0f

void UpdateDialSpring(ClockState *clock)
{
    if (clock->draggingDial) return;

    const float springStrength = 256.0f;
    const float damping = 8.0f;
    float dt = GetFrameTime();
    if (dt <= 0.0f) return;

    float acceleration = -springStrength * clock->dialAngle
                       - damping * clock->dialAngularVelocity;
    clock->dialAngularVelocity += acceleration * dt;
    clock->dialAngle += clock->dialAngularVelocity * dt;

    if (fabsf(clock->dialAngle) < 0.001f && fabsf(clock->dialAngularVelocity) < 0.001f) {
        clock->dialAngle = 0.0f;
        clock->dialAngularVelocity = 0.0f;
    }
}

void HandleClockInput(ClockState *clock, Vector2 mouse, Vector2 center) {
    UpdateDialSpring(clock);

    Vector2 hourEnd = GetHandEnd(center, clock->hourHandLength, clock->hourAngle);
    Vector2 minuteEnd = GetHandEnd(center, clock->minuteHandLength, clock->minuteAngle);
    Vector2 secondEnd = GetHandEnd(center, clock->secondHandLength, clock->secondAngle);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (IsNear(center, hourEnd, mouse)) {
            clock->draggingHour = true;
            clock->returningHour = false;
            clock->hourAngularVelocity = 0.0f;
        }
        else if (IsNear(center, minuteEnd, mouse)) {
            clock->draggingMinute = true;
            clock->returningMinute = false;
            clock->minuteAngularVelocity = 0.0f;
        }
        else if (IsNear(center, secondEnd, mouse)) {
            clock->draggingSecond = true;
            clock->returningSecond = false;
            clock->secondAngularVelocity = 0.0f;
        }
        else
        {
            float dist = sqrtf(pow(mouse.x - center.x, 2.0) + pow(mouse.y - center.y, 2.0));
            float dialInnerRadius = clock->clockRadius *
                (1.0f - MINUTE_MARKER_LENGTH_FACTOR);

            if (dist >= dialInnerRadius && dist <= clock->clockRadius) {
                clock->draggingDial = true;
                clock->dialWasDragged = false;
                clock->dialAngularVelocity = 0.0f;
                clock->lastDialMouseAngle = GetMouseAngle(mouse, center);
                clock->dialPressMouse = mouse;
            }
            else if (dist <= clock->clockRadius) clock->clockColor = RandomColor();
            else clock->bgColor = RandomColor();
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        if (clock->draggingHour) clock->returningHour = true;
        if (clock->draggingMinute) clock->returningMinute = true;
        if (clock->draggingSecond) clock->returningSecond = true;
        clock->draggingHour = clock->draggingMinute = clock->draggingSecond = false;

        if (clock->draggingDial) {
            float pressDx = mouse.x - clock->dialPressMouse.x;
            float pressDy = mouse.y - clock->dialPressMouse.y;
            float thresholdSquared = DIAL_DRAG_THRESHOLD * DIAL_DRAG_THRESHOLD;
            if (pressDx * pressDx + pressDy * pressDy >= thresholdSquared) {
                clock->dialWasDragged = true;
            }
            if (!clock->dialWasDragged) {
                clock->hourMarkerColor = RandomColor();
                clock->minuteMarkerColor = RandomColor();
            }
        }
        clock->draggingDial = false;
    }

    float mouseAngle = GetMouseAngle(mouse, center);

    float dt = GetFrameTime();
    if (clock->draggingHour) {
        float angleDelta = NormalizeAngle((PI - mouseAngle) - clock->hourAngle);
        clock->hourAngle += angleDelta;
        if (dt > 0.0f) clock->hourAngularVelocity = angleDelta / dt;
    }
    if (clock->draggingMinute) {
        float angleDelta = NormalizeAngle((PI - mouseAngle) - clock->minuteAngle);
        clock->minuteAngle += angleDelta;
        if (dt > 0.0f) clock->minuteAngularVelocity = angleDelta / dt;
    }
    if (clock->draggingSecond) {
        float angleDelta = NormalizeAngle((PI - mouseAngle) - clock->secondAngle);
        clock->secondAngle += angleDelta;
        if (dt > 0.0f) clock->secondAngularVelocity = angleDelta / dt;
    }

    if (clock->draggingDial) {
        float pressDx = mouse.x - clock->dialPressMouse.x;
        float pressDy = mouse.y - clock->dialPressMouse.y;
        float thresholdSquared = DIAL_DRAG_THRESHOLD * DIAL_DRAG_THRESHOLD;
        if (!clock->dialWasDragged &&
            pressDx * pressDx + pressDy * pressDy >= thresholdSquared) {
            clock->dialWasDragged = true;
            clock->lastDialMouseAngle = mouseAngle;
            clock->dialAngularVelocity = 0.0f;
        }

        if (!clock->dialWasDragged) return;

        float angleDelta = NormalizeAngle(mouseAngle - clock->lastDialMouseAngle);
        // The marker ring is viewed as a physical dial, so it rotates opposite
        // to the cursor's polar-angle change.
        clock->dialAngle -= angleDelta;
        clock->lastDialMouseAngle = mouseAngle;

        if (dt > 0.0f) clock->dialAngularVelocity = -angleDelta / dt;

    }
}

#endif // CLOCK_INPUT_H
