add_library(rlimgui
    rlImGui.cpp
)

add_library(rlImGui ALIAS rlimgui)

target_include_directories(rlimgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(rlimgui PUBLIC
    NO_FONT_AWESOME
)

target_link_libraries(rlimgui
    PUBLIC
    raylib
    imgui
)
