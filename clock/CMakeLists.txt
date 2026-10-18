aux_source_directory(src clock_src)
file(GLOB_RECURSE clock_headers include/*h)

add_executable(analog-clock ${clock_src} ${clock_headers})
target_include_directories(analog-clock PRIVATE include)
target_link_libraries(analog-clock PRIVATE raylib)

add_custom_command(TARGET analog-clock POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:analog-clock>
        $<TARGET_FILE_DIR:analog-clock>
    COMMAND_EXPAND_LISTS
)

add_custom_command(TARGET analog-clock POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:analog-clock>/assets"
)

if (WIN32)
    target_sources(analog-clock PRIVATE resources/app.rc)
endif()