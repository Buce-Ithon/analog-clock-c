#ifndef CLOCK_INPUT_H
#define CLOCK_INPUT_H

#include <raylib.h>
#include "clock.h"
#include "clock_math.h"

void HandleClockInput(ClockState *clock, Vector2 mouse, Vector2 center) {
    Vector2 hourEnd = GetHandEnd(center, clock->hourHandLength, clock->hourAngle);
    Vector2 minuteEnd = GetHandEnd(center, clock->minuteHandLength, clock->minuteAngle);
    Vector2 secondEnd = GetHandEnd(center, clock->secondHandLength, clock->secondAngle);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (IsNear(center, hourEnd, mouse)) clock->draggingHour = true;
        else if (IsNear(center, minuteEnd, mouse)) clock->draggingMinute = true;
        else if (IsNear(center, secondEnd, mouse)) clock->draggingSecond = true;
        else
        {
            float dist = sqrtf(pow(mouse.x - center.x, 2.0) + pow(mouse.y - center.y, 2.0));
            if (dist <= clock->clockRadius) clock->clockColor = RandomColor();
            else clock->bgColor = RandomColor();
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        clock->draggingHour = clock->draggingMinute = clock->draggingSecond = false;
    }

    float mouseAngle = GetMouseAngle(mouse, center);

    if (clock->draggingHour) clock->hourAngle = PI-mouseAngle;
    if (clock->draggingMinute) clock->minuteAngle = PI-mouseAngle;
    if (clock->draggingSecond) clock->secondAngle = PI-mouseAngle;
}

#endif // CLOCK_INPUT_H