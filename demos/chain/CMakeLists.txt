add_library(chain_demo
    ChainDemo.cpp
)

target_include_directories(chain_demo PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(chain_demo PUBLIC
    engine
)