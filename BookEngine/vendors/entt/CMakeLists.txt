add_subdirectory(entt)

add_library(${TARGET_ECS} INTERFACE)

target_link_libraries(${TARGET_ECS} INTERFACE EnTT::EnTT)
