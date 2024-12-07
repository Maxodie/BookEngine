#file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/glm/*.hpp)
#file(GLOB_RECURSE headers1 ${CMAKE_CURRENT_SOURCE_DIR}/include/glm/*.h)
#file(GLOB_RECURSE inlines ${CMAKE_CURRENT_SOURCE_DIR}/include/glm/*.inl)
#add_library(${TARGET_MATH} INTERFACE headers headers1 inlines)

add_subdirectory(include/glm)

add_library(${TARGET_MATH} INTERFACE)

target_include_directories(${TARGET_MATH} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(${TARGET_MATH} INTERFACE glm::glm)
