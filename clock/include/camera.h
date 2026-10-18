#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

void UpdateClockCamera(Camera2D *camera, int width, int height) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    float scaleX = (float) screenWidth / width;
    float scaleY = (float) screenHeight / height;
    
    camera->zoom = (scaleX < scaleY) ? scaleX : scaleY;
    camera->target = (Vector2){width / 2.0f, height / 2.0f};
    camera->offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
}

#endif // CAMERA_H