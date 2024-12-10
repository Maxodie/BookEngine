project(Engine)

# gather all source files
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE sources1 ${CMAKE_CURRENT_SOURCE_DIR}/includes/*.cpp)
file(GLOB_RECURSE headers1 ${CMAKE_CURRENT_SOURCE_DIR}/includes/*.hpp)

# sub directories #####
add_subdirectory(vendors/assimp)
add_subdirectory(vendors/spdlog)
add_subdirectory(vendors/GLFW)
add_subdirectory(vendors/Glad)
add_subdirectory(vendors/glm)
add_subdirectory(vendors/entt)

add_library(${PROJECT_NAME} SHARED ${sources} ${sources1} ${headers} ${headers1})

# precompiled headers
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/BookPch.hpp)

# export engine symbols
target_compile_definitions(${PROJECT_NAME} PUBLIC -DBOOK_EXPORT)# SPDLOG_FMT_EXTERNAL)

# includes directories
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

# link libraries
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
    ${TARGET_LOGGER}
    ${TARGET_WINDOW}
    ${TARGET_RENDERER}
    ${TARGET_MATH}
    ${TARGET_ECS}
    ${TARGET_MODEL_LOADER}
)

# copy resources
if(EXISTS ${CMAKE_SOURCE_DIR}/Resources)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources
        ${EXECUTABLE_OUTPUT_PATH}/Resources
    )
else()
    message(WARNING "[WARNING] no resources directory !")
endif()
