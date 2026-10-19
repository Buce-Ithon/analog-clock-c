#ifndef CLOCK_SETTINGS_H
#define CLOCK_SETTINGS_H

#include <math.h>
#include <raygui/raygui.h>
#include "clock.h"

static void DrawClockColorControl(Rectangle bounds, const char *label,
                                  Color *color, bool showAlpha)
{
    GuiLabel((Rectangle){bounds.x, bounds.y, bounds.width, 18}, label);
    GuiColorPicker((Rectangle){bounds.x, bounds.y + 20, 94, 76}, NULL, color);

    if (showAlpha) {
        float alpha = (float)color->a / 255.0f;
        GuiColorBarAlpha((Rectangle){bounds.x, bounds.y + 102, 112, 16},
                         "Alpha", &alpha);
        color->a = (unsigned char)roundf(alpha * 255.0f);
    }
}

static void ResetClockSettings(ClockState *clock)
{
    clock->tuning.dialSpringStrength = 256.0f;
    clock->tuning.dialDamping = 8.0f;
    clock->tuning.handSpringStrength = 512.0f;
    clock->tuning.handDamping = 10.0f;
    clock->bgColor = (Color){31, 35, 53, 135};
    clock->clockColor = RAYWHITE;
    clock->hourMarkerColor = GRAY;
    clock->minuteMarkerColor = GRAY;
}

static void DrawClockSettingsPanel(ClockState *clock)
{
    const float panelWidth = 300.0f;
    const float panelHeight = 480.0f;
    float panelX = (float)GetScreenWidth() - panelWidth - 12.0f;
    if (panelX < 12.0f) panelX = 12.0f;

    Rectangle panel = {panelX, 12.0f, panelWidth, panelHeight};
    GuiPanel(panel, "Clock settings  [M]");

    float controlX = panel.x + 12.0f;
    float controlWidth = panel.width - 24.0f;
    GuiLabel((Rectangle){controlX, panel.y + 30.0f, controlWidth, 18}, "Spring response");
    GuiSlider((Rectangle){controlX, panel.y + 50.0f, controlWidth, 20.0f},
              "Dial spring", TextFormat("%.0f", clock->tuning.dialSpringStrength),
              &clock->tuning.dialSpringStrength, 0.0f, 1000.0f);
    GuiSlider((Rectangle){controlX, panel.y + 76.0f, controlWidth, 20.0f},
              "Dial damping", TextFormat("%.1f", clock->tuning.dialDamping),
              &clock->tuning.dialDamping, 0.0f, 100.0f);
    GuiSlider((Rectangle){controlX, panel.y + 102.0f, controlWidth, 20.0f},
              "Hand spring", TextFormat("%.0f", clock->tuning.handSpringStrength),
              &clock->tuning.handSpringStrength, 0.0f, 1000.0f);
    GuiSlider((Rectangle){controlX, panel.y + 128.0f, controlWidth, 20.0f},
              "Hand damping", TextFormat("%.1f", clock->tuning.handDamping),
              &clock->tuning.handDamping, 0.0f, 100.0f);

    GuiLabel((Rectangle){controlX, panel.y + 158.0f, controlWidth, 18}, "Colors");
    DrawClockColorControl((Rectangle){controlX, panel.y + 180.0f, 120.0f, 118.0f},
                          "Background", &clock->bgColor, true);
    DrawClockColorControl((Rectangle){controlX + 150.0f, panel.y + 180.0f, 120.0f, 118.0f},
                          "Dial", &clock->clockColor, false);
    DrawClockColorControl((Rectangle){controlX, panel.y + 310.0f, 120.0f, 118.0f},
                          "Hour markers", &clock->hourMarkerColor, false);
    DrawClockColorControl((Rectangle){controlX + 150.0f, panel.y + 310.0f, 120.0f, 118.0f},
                          "Minute markers", &clock->minuteMarkerColor, false);

    if (GuiButton((Rectangle){controlX, panel.y + 442.0f, controlWidth, 26.0f},
                  "Restore defaults")) {
        ResetClockSettings(clock);
    }
}

#endif // CLOCK_SETTINGS_H
