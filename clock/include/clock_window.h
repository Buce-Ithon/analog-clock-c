#ifndef CLOCK_WINDOW_H
#define CLOCK_WINDOW_H

#include <raylib.h>
#include "windows_acrylic.h"

static void InitializeClockWindow(int width, int height)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT |
                   FLAG_WINDOW_TRANSPARENT);
    InitWindow(width, height, "Analog Clock");
    EnableWindowsAcrylic();

    Image icon = LoadImage("assets/icon.png");
    if (icon.data != NULL) {
        ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        SetWindowIcon(icon);
        UnloadImage(icon);
    }
}

#endif // CLOCK_WINDOW_H
