add_library(stress_test
    StressTest.cpp
)

target_include_directories(stress_test PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(stress_test PUBLIC
    engine
)