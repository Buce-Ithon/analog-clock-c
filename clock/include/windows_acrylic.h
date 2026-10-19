#ifndef WINDOWS_ACRYLIC_H
#define WINDOWS_ACRYLIC_H

#include <raylib.h>
#include <stddef.h>

// Keep <windows.h> out of this project: Windows GDI's Rectangle() function
// collides with raylib's Rectangle type.  Only the required API is declared.
#if defined(_WIN32)

#ifndef WINAPI
#define WINAPI __stdcall
#endif

typedef void *AcrylicModuleHandle;
typedef int AcrylicBool;

__declspec(dllimport) AcrylicModuleHandle WINAPI GetModuleHandleA(const char *moduleName);
__declspec(dllimport) AcrylicModuleHandle WINAPI LoadLibraryA(const char *fileName);
__declspec(dllimport) void *WINAPI GetProcAddress(AcrylicModuleHandle module, const char *name);

typedef long (WINAPI *DwmSetWindowAttributeFn)(
    void *windowHandle, unsigned int attribute, const void *value, unsigned int valueSize);

enum {
    DWMWA_USE_IMMERSIVE_DARK_MODE = 20,
    DWMWA_SYSTEMBACKDROP_TYPE = 38,
    DWMSBT_NONE = 1,
    DWMSBT_TRANSIENTWINDOW = 3
};

static DwmSetWindowAttributeFn GetDwmSetWindowAttribute(void)
{
    AcrylicModuleHandle dwmapi = LoadLibraryA("dwmapi.dll");
    if (dwmapi == NULL) return NULL;

    return (DwmSetWindowAttributeFn)GetProcAddress(dwmapi, "DwmSetWindowAttribute");
}

// Call once after InitWindow(). Requires Windows 11 build 22621 or later.
// This is the documented Desktop Acrylic backdrop and includes the title bar.
static bool EnableWindowsAcrylic(void)
{
    DwmSetWindowAttributeFn setDwmAttribute = GetDwmSetWindowAttribute();
    if (setDwmAttribute == NULL) return false;

    AcrylicBool useDarkMode = 1;
    int backdrop = DWMSBT_TRANSIENTWINDOW;
    void *windowHandle = GetWindowHandle();

    // Dark mode makes the title text/buttons remain legible when the system
    // applies its non-client-area updates during drag, resize, or activation.
    setDwmAttribute(windowHandle, DWMWA_USE_IMMERSIVE_DARK_MODE,
        &useDarkMode, sizeof(useDarkMode));

    return setDwmAttribute(windowHandle, DWMWA_SYSTEMBACKDROP_TYPE,
        &backdrop, sizeof(backdrop)) == 0;
}

static void DisableWindowsAcrylic(void)
{
    DwmSetWindowAttributeFn setDwmAttribute = GetDwmSetWindowAttribute();
    if (setDwmAttribute == NULL) return;

    int backdrop = DWMSBT_NONE;
    setDwmAttribute(GetWindowHandle(), DWMWA_SYSTEMBACKDROP_TYPE,
        &backdrop, sizeof(backdrop));
}

#else

static bool EnableWindowsAcrylic(void)
{
    return false;
}

static void DisableWindowsAcrylic(void) { }

#endif // _WIN32

#endif // WINDOWS_ACRYLIC_H