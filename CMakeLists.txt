cmake_minimum_required(VERSION 4.2.0)

project(analog-clock
    DESCRIPTION "An analog clock project using C."
    LANGUAGES C
)

include(cmake/ConfigureOptions.cmake)

add_subdirectory(third_party)
add_subdirectory(clock)