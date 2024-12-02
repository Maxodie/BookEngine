project(Engine)

# gather all source files
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE sources1 ${CMAKE_CURRENT_SOURCE_DIR}/includes/*.cpp)
file(GLOB_RECURSE headers1 ${CMAKE_CURRENT_SOURCE_DIR}/includes/*.hpp)

# sub directories #####
add_subdirectory(vendors/spdlog)
#######################

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
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${TARGET_LOGGER})
