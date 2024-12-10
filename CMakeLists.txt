cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TARGET_LOGGER spdlog_header_only)
set(TARGET_WINDOW glfw_window)
set(TARGET_RENDERER glad_opengl)
set(TARGET_MATH glm_math)
set(TARGET_ECS entt_ecs)
set(TARGET_MODEL_LOADER assimp_model_loader)

# build output directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/lib)
set(CMAKE_PDB_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH$<0:>${CMAKE_BINARY_DIR}/bin)

# cpp standard options
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
project(BookEngine)

message(STATUS "${CMAKE_BUILD_TYPE} build")
# enable console loggin
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    message(STATUS "Log Enabled")
    add_definitions(-DBOOK_ENABLE_LOG)
endif()

# project subdirectories
add_subdirectory(BookEngine)
add_subdirectory(BookEditor)
add_subdirectory(BookGame)

# Specify a custom location for compile_commands.json
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
        RESULT_VARIABLE result
    )
    if(result)
        message(WARNING "Failed to create copy for compile_commands.json. Result: ${result}")
    endif()
endif()
