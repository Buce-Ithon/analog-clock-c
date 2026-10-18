# Introduction.

This is a practise project for trying raylib and improve CMake project management. As you could see, it is an **analog clock** written in C because it is simple enough but still educational.

And this project is primarily inspired by [this video](https://www.youtube.com/watch?v=2jSpSTXMvlk) made by this [author](https://www.youtube.com/@HirschDaniel), which provided a very detailed explanation of the entire project process. If you want to learn more about it, consider watch this video.

What's new of this project is that I use CMake to make a (maybe) better build solution and I also seperate the parts of original project and manage them as single modules (header files) to make it seems clearly. Moreover, I also add some new interesting interactive features, to make it more "vivid"~ So enjoy it.

# How to build?

Required (this project is built on Windows):
- CMake (Version >= 3.*, even I use 4.2.0)
- MSVC/GCC/Clang (one of them three)
- Ninja (recommended)
- A pre-compiled Raylib library installed

## Build quickly.

```bash
cmake --preset ninja-debug -DRAYLIB_ROOT_PATH="D:/path/to/raylib"
cmake --build --preset ninja-debug
```

or simply
```bash
cmake -S . -B build -DRAYLIB_ROOT_PATH="D:/path/to/raylib"
cmake --build build
```

## Build "in a relatively cumbersome manner".

The best way is to rewrite a new `CMakeUserPresets.json` based on the given template `CMakePresets.json`, where you could use CMake `inherit` method or just copy most of them, and add the `RAYLIB_ROOT_PATH` (one of `cacheVariables` in `configurePresets`) to indicate the location of Raylib library installed.

For example:
```json
{
    "configurePresets": [
        {
            "name": "ninja-local-debug",
            "displayName": "Ninja (Debug) (Local)",
            "generator": "Ninja",
            "binaryDir": "${sourceDir}/build/ninja/debug",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "CMAKE_INSTALL_PREFIX": "${sourceDir}/install/ninja/debug",
                "RAYLIB_ROOT_PATH": "D:/path/to/raylib"
            }
        },
        {
            "name": "ninja-local-release",
            "displayName": "Ninja (Release) (Local)",
            "generator": "Ninja",
            "binaryDir": "${sourceDir}/build/ninja/release",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release",
                "CMAKE_INSTALL_PREFIX": "${sourceDir}/install/ninja/release",
                "RAYLIB_ROOT_PATH": "D:/path/to/raylib"
            }
        },
        {
            "name": "msvc-local",
            "displayName": "Visual Studio 17 2022 (Local)",
            "generator": "Visual Studio 17 2022",
            "binaryDir": "${sourceDir}/build/msvc",
            "cacheVariables": {
                "CMAKE_INSTALL_PREFIX": "${sourceDir}/install/msvc",
                "RAYLIB_ROOT_PATH": "D:/path/to/raylib"
            }
        }
    ],
    "buildPresets": [
        {
            "name": "ninja-local-debug",
            "configurePreset": "ninja-local-debug",
            "jobs": 8
        },
        {
            "name": "ninja-local-release",
            "configurePreset": "ninja-local-release",
            "jobs": 8
        },
        {
            "name": "msvc-local-debug",
            "configurePreset": "msvc-local",
            "configuration": "Debug",
            "jobs": 8
        },
        {
            "name": "msvc-local-release",
            "configurePreset": "msvc-local",
            "configuration": "Release",
            "jobs": 8
        }
    ]
}
```

After that, you could use the following commands to build whole project:
```bash
cmake --preset <choose-a-configure-preset> # for example "msvc-local"
cmake --build --preset <choose-a-configure-preset> # for example "msvc-local-debug"
```