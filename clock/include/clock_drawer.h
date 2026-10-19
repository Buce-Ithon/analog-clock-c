#ifndef CLOCK_DRAWER_H
#define CLOCK_DRAWER_H

#include <math.h>
#include <stdio.h>

#include <raylib.h>
#include "clock.h"

void DrawMinuteMarkers(Vector2 center, float clockRadius, float rotation,
                       Color hourColor, Color minuteColor)
{
    float alpha = rotation;
    for (int i = 0; i < 60; i++)
    {
        bool isHour = (i % 5 == 0);

        float innerFactor = isHour ? 0.86f : 0.90f;
        float outerFactor = 0.98f;
        float thickness = isHour ? 4.0f : 3.0f;

        float x_inner = clockRadius * innerFactor * sinf(alpha) + center.x;
        float y_inner = clockRadius * innerFactor * cosf(alpha) + center.y;
        Vector2 inner = {x_inner, y_inner};

        float x_outer = clockRadius * outerFactor * sinf(alpha) + center.x;
        float y_outer = clockRadius * outerFactor * cosf(alpha) + center.y;
        Vector2 outer = {x_outer, y_outer};

        DrawLineEx(inner, outer, thickness, isHour ? hourColor : minuteColor);

        alpha += (2.0f * PI) / 60.0f;
    }
}

void DrawHourNumbers(Vector2 center, float clockRadius, Color color)
{
    const int fontSize = 30;
    const float radius = clockRadius * 0.80f;

    for (int i = 1; i <= 12; i++)
    {
        float alpha = PI - i * (PI / 6.0f);
        float x = radius * sinf(alpha) + center.x;
        float y = radius * cosf(alpha) + center.y;

        char text[3];
        sprintf(text, "%d", i);
        int textWidth = MeasureText(text, fontSize);

        DrawText(text, (int)(x - (float)textWidth / 2), (int)(y - (float)fontSize / 2), fontSize, color);
    }
}

void DrawHand(Vector2 center, float length, float angle, float thickness, Color color)
{
    Vector2 end = {length * sinf(angle) + center.x, length * cosf(angle) + center.y};

    DrawLineEx(center, end, thickness, color);
}

void DrawClock(const ClockState *clock, Vector2 center) {
    DrawCircleV(center, clock->clockRadius, clock->clockColor);
    DrawMinuteMarkers(center, clock->clockRadius, clock->dialAngle,
                      clock->hourMarkerColor, clock->minuteMarkerColor);
    DrawHourNumbers(center, clock->clockRadius, BLACK);

    DrawHand(center, clock->hourHandLength, clock->hourAngle, 5, BLACK);
    DrawHand(center, clock->minuteHandLength, clock->minuteAngle, 4, SKYBLUE);
    DrawHand(center, clock->secondHandLength, clock->secondAngle, 3, GRAY);

    DrawCircleV(center, 6, BLACK);
}

#endif // CLOCK_DRAWER_H
