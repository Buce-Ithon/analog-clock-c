#include "clock.h"
#include "clock_drawer.h"
#include "clock_time.h"
#include "clock_input.h"
#define RAYGUI_IMPLEMENTATION
#include "clock_settings.h"
#include "camera.h"
#include "clock_window.h"
#include <raylib.h>

const int width = 600;
const int height = 600;
const Vector2 center = {300.0f, 300.0f};

int main() {
    InitializeClockWindow(width, height);

    Camera2D camera = {0};
    camera.zoom = 1.0f;

    ClockState clock = ClockInit(center, height);
    bool showSettingsPanel = false;
    
    while(!WindowShouldClose()) {
        HandleClockKeyboardInput(&clock, &showSettingsPanel);

        UpdateClockTime(&clock);

        Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera);

        if (!showSettingsPanel) HandleClockInput(&clock, mouse, center);

        UpdateClockCamera(&camera, width, height);

        BeginDrawing();
        ClearBackground(clock.bgColor);

        BeginMode2D(camera);
        DrawClock(&clock, center);
        EndMode2D();

        if (showSettingsPanel) DrawClockSettingsPanel(&clock);

        EndDrawing();
    }

    DisableWindowsAcrylic();
    CloseWindow();
    return 0;
}
