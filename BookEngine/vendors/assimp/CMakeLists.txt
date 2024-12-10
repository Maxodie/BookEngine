# Disable tests build
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable Tests build" FORCE)
# Disable treating warnings as errors
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Treat warnings as errors" FORCE)
# Disable Assimp's export functionality
set(ASSIMP_NO_EXPORT ON CACHE BOOL "Disable Assimp export functionality" FORCE)
# Enable static library instead of shared
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Assimp as a static library" FORCE)
# Set additional options as needed
set(ASSIMP_INSTALL OFF CACHE BOOL "Don't install Assimp" FORCE)

set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "Don't install Assimp" FORCE)

add_subdirectory(include)
#find_package(assimp REQUIRED)
add_library(${TARGET_MODEL_LOADER} INTERFACE)

target_link_libraries(${TARGET_MODEL_LOADER} INTERFACE assimp::assimp)
