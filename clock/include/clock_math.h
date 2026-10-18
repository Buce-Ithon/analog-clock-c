#ifndef CLOCK_MATH_H
#define CLOCK_MATH_H

#include <math.h>
#include <raylib.h>

Color RandomColor()
{
    return (Color){GetRandomValue(15,245), GetRandomValue(15,245), GetRandomValue(15,245), GetRandomValue(127,255)};
}

float GetMouseAngle(Vector2 mouse, Vector2 center)
{
    // Make sure the sign of dx and dy is same as in Cartesian coordinate.
    float dx = mouse.x - center.x;
    float dy = center.y - mouse.y;
    // The angle = 0 when measured vertically upward from center, and increases in clockwise direction.
    return atan2f(dx, dy);
}

bool IsNear(Vector2 p1, Vector2 p2, Vector2 mouse)
{
    /* 1st edition
    // Calculate the distance from point mouse to the line constructed by p1 and p2.
    // d = (A*x_0+B*y_0+C)/sqrt(A^2+B^2)
    float d = fabsf((p2.y - p1.y) * mouse.x - (p2.x-p1.x) * mouse.y + p2.x * p1.y - p2.y * p1.x) / sqrtf(pow(p1.x - p2.x, 2.0) + pow(p1.y - p2.y, 2.0));
    // Edge condition.
    return (d < 10.0f);
    */
    Vector2 line = {p2.x - p1.x, p2.y - p1.y};
    Vector2 toMouse = {mouse.x - p1.x, mouse.y - p1.y};
    // 1. Check whether the projection falls with the segment.
    float dot = toMouse.x * line.x +toMouse.y * line.y;
    float lengthSquared = line.x * line.x + line.y * line.y;

    if (lengthSquared == 0.0f) {
        // p1 and p2 are the same point.
        float dx = mouse.x - p1.x;
        float dy = mouse.y - p1.y;
        return dx * dx + dy * dy < 100.0f;
    }
    
    if (dot < 0.0f || dot > lengthSquared) {
        return false;
    }
    
    // 2. Check the perpendiculae distance to the line.
    float cross = line.x * toMouse.y - line.y * toMouse.x;
    float distanceSquared = (cross * cross) / lengthSquared;
    return distanceSquared < 100.0f;
}

Vector2 GetHandEnd(Vector2 center, float length, float angle) {
    return (Vector2){center.x + length * sinf(angle), center.y + length * cosf(angle)};
}

#endif // CLOCK_MATH_H