project(Game)

# gather source files
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
add_executable(${PROJECT_NAME} ${sources} ${headers})

# include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Engine)
