set(RAYLIB_ROOT_PATH "" CACHE PATH "The raylib pre-compild library directory.")

if(NOT RAYLIB_ROOT_PATH)
    message(FATAL_ERROR
        "Raylib was not configured.\n"
        "Please specify -DRAYLIB_ROOT_PATH=<path> when configuring.\n"
        "Example: cmake -S . -B build -DRAYLIB_ROOT_PATH=<path>\n"
    )
else()
    message(
        "Successfully find raylib: ${RAYLIB_ROOT_PATH}"
    )
endif()

add_library(raylib SHARED IMPORTED GLOBAL)
set_target_properties(raylib PROPERTIES    
    IMPORTED_LOCATION "${RAYLIB_ROOT_PATH}/lib/raylib.dll"
    IMPORTED_IMPLIB "${RAYLIB_ROOT_PATH}/lib/raylibdll.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_ROOT_PATH}/include"
    # same as target_include_directories(raylib INTERFACE "${RAYLIB_ROOT_PATH}/include")
)