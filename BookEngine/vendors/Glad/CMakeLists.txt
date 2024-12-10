add_library(${TARGET_RENDERER} "include/src/glad.c")

target_include_directories(${TARGET_RENDERER} PUBLIC
    include/include
)
