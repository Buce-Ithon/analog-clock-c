#include "clock.h"
#include "clock_drawer.h"
#include "clock_time.h"
#include "clock_input.h"
#define RAYGUI_IMPLEMENTATION
#include "clock_settings.h"
#include "camera.h"
#include "windows_acrylic.h"
#include <raylib.h>

const int width = 600;
const int height = 600;
const Vector2 center = {300.0f, 300.0f};

int main() {
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

    Camera2D camera = {0};
    camera.zoom = 1.0f;

    ClockState clock = ClockInit(center, height);
    bool showSettingsPanel = false;
    
    while(!WindowShouldClose()) {
        if (IsKeyPressed(KEY_M)) {
            showSettingsPanel = !showSettingsPanel;
            if (showSettingsPanel) CancelClockInteraction(&clock);
        }

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
