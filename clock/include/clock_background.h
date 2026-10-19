#ifndef FROSTED_BACKGROUND_H
#define FROSTED_BACKGROUND_H

#include <raylib.h>

// Header-only helper.  Its state has internal linkage, so include it from the
// one translation unit that draws the application's background.
static RenderTexture2D frostedBackgroundTarget = {0};
static Shader frostedBackgroundShader = {0};
static Texture2D frostedBackgroundNoise = {0};
static int frostedBackgroundNoiseLocation = -1;
static int frostedBackgroundTimeLocation = -1;

static void FrostedBackgroundEnsureResources(void)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    if (frostedBackgroundShader.id == 0)
    {
        frostedBackgroundShader = LoadShader(NULL, "assets/shaders/frosted_glass.fs");
        frostedBackgroundNoiseLocation = GetShaderLocation(frostedBackgroundShader, "noiseTexture");
        frostedBackgroundTimeLocation = GetShaderLocation(frostedBackgroundShader, "time");

        // The Shadertoy effect uses iChannel1 as a repeatable noise source.
        Image noiseImage = GenImageWhiteNoise(128, 128, 0.5f);
        frostedBackgroundNoise = LoadTextureFromImage(noiseImage);
        UnloadImage(noiseImage);
        SetTextureWrap(frostedBackgroundNoise, TEXTURE_WRAP_REPEAT);
        SetTextureFilter(frostedBackgroundNoise, TEXTURE_FILTER_BILINEAR);
        SetShaderValueTexture(frostedBackgroundShader,
            frostedBackgroundNoiseLocation, frostedBackgroundNoise);
    }

    if (frostedBackgroundTarget.id == 0)
    {
        frostedBackgroundTarget = LoadRenderTexture(width, height);
    }
    else if (frostedBackgroundTarget.texture.width != width ||
             frostedBackgroundTarget.texture.height != height)
    {
        UnloadRenderTexture(frostedBackgroundTarget);
        frostedBackgroundTarget = LoadRenderTexture(width, height);
    }
}

// Call this inside BeginDrawing()/EndDrawing() in place of ClearBackground().
// The colour remains the shader input, so existing background colour changes
// still work without any other drawing changes.
static void DrawFrostedBackground(Color backgroundColor)
{
    FrostedBackgroundEnsureResources();

    BeginTextureMode(frostedBackgroundTarget);
    ClearBackground(backgroundColor);
    EndTextureMode();

    float time = (float)GetTime();
    SetShaderValue(frostedBackgroundShader, frostedBackgroundTimeLocation,
        &time, SHADER_UNIFORM_FLOAT);

    BeginShaderMode(frostedBackgroundShader);
    DrawTextureRec(frostedBackgroundTarget.texture,
        (Rectangle){0, 0, (float)frostedBackgroundTarget.texture.width,
                    -(float)frostedBackgroundTarget.texture.height},
        (Vector2){0, 0}, WHITE);
    EndShaderMode();
}

static void UnloadFrostedBackground(void)
{
    if (frostedBackgroundTarget.id != 0) UnloadRenderTexture(frostedBackgroundTarget);
    if (frostedBackgroundNoise.id != 0) UnloadTexture(frostedBackgroundNoise);
    if (frostedBackgroundShader.id != 0) UnloadShader(frostedBackgroundShader);
}

#endif // FROSTED_BACKGROUND_H