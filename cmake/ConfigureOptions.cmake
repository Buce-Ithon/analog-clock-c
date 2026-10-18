set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_GENERATOR MATCHES "Makefiles|Ninja")
	if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
		add_custom_target(
			CopyCompileCommands ALL
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${CMAKE_BINARY_DIR}/compile_commands.json
				${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
			DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
			COMMENT "Copy compile_commands.json to the project source directory."
		)
	endif()
endif()